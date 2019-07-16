/* Copyright (C) 2008-2009 MontaVista Software Inc.
 * Copyright (C) 2008-2009 Texas Instruments Inc
 * Copyright (C) 2017 Steward Fu <steward.fu@gmail.com>
 * Copyright (C) 2019 Eason Chen <easonchen@eecgroup.com.tw>
 *
 * AM335x framebuffer driver for RA8875 LCD panel
 *
 * Based on the LCD driver for TI Avalanche processors written by
 * Ajay Singh and Shalom Hai.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option)any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fb.h>
#include <linux/dma-mapping.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/pm_runtime.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/clk.h>
#include <linux/cpufreq.h>
#include <linux/console.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/lcm.h>
#include <linux/clk-provider.h>
#include <video/of_display_timing.h>
#include <linux/gpio.h>
#include <asm/div64.h>
 
#define DRIVER_NAME "am335x_lcdc"
 
#define do_request(pin, name) \
  if(gpio_request(pin, name) < 0){ \
    printk("failed to request gpio: %s\n", name); \
  } \
  else{ \
    printk("request successfully for gpio: %s\n", name); \
    gpio_direction_output(pin, 1); \
  }
 
#define PALETTE_SIZE          256
 
#define ILI9335_SLCD_D17      77
#define ILI9335_SLCD_D16      76
#define ILI9335_SLCD_D15      75
#define ILI9335_SLCD_D14      74
#define ILI9335_SLCD_D13      73
#define ILI9335_SLCD_D12      72
#define ILI9335_SLCD_D11      71
#define ILI9335_SLCD_D10      70
#define ILI9335_SLCD_RS       86
#define ILI9335_SLCD_CS       89
#define ILI9335_SLCD_RD       88
#define ILI9335_SLCD_WR       87
#define ILI9335_SLCD_RST      20
 
#define PID                   0x0
#define CTRL                  0x4
#define LIDD_CTRL             0xC
#define LIDD_CS0_CONF         0x10
#define LIDD_CS0_ADDR         0x14
#define LIDD_CS0_DATA         0x18
#define LIDD_CS1_CONF         0x1C
#define LIDD_CS1_ADDR         0x20
#define LIDD_CS1_DATA         0x24
#define RASTER_CTRL           0x28
#define RASTER_TIMING_0       0x2C
#define RASTER_TIMING_1       0x30
#define RASTER_TIMING_2       0x34
#define RASTER_SUBPANEL       0x38
#define RASTER_SUBPANEL2      0x3C
#define LCDDMA_CTRL           0x40
#define LCDDMA_FB0_BASE       0x44
#define LCDDMA_FB0_CEILING    0x48
#define LCDDMA_FB1_BASE       0x4C
#define LCDDMA_FB1_CEILING    0x50
#define SYSCONFIG             0x54
#define IRQSTATUS_RAW         0x58
#define IRQSTATUS             0x5C
#define IRQENABLE_SET         0x60
#define IRQENABLE_CLEAR       0x64
#define CLKC_ENABLE           0x6C
#define CLKC_RESET            0x70
 
struct am335x_fb_par {
  struct device *dev;
 
  resource_size_t p_palette_base;
  unsigned char *v_palette_base;
 
  dma_addr_t vram_phys;
  unsigned long vram_size;
  void *vram_virt;
 
  dma_addr_t lram_phys;
  unsigned long lram_size;
  void *lram_virt;
 
  unsigned int dma_start;
  unsigned int dma_end;
 
  int irq;
  u32 pseudo_palette[16];
  struct fb_videomode mode;
  unsigned int bpp;
};
 
static struct resource *lcdc_regs;
static void __iomem *am335x_fb_reg_base;
static struct fb_var_screeninfo am335x_fb_var;
static struct fb_fix_screeninfo am335x_fb_fix = {
  .id = "AM335x FB",
  .type = FB_TYPE_PACKED_PIXELS,
  .type_aux = 0,
  .visual = FB_VISUAL_PSEUDOCOLOR,
  .xpanstep = 0,
  .ypanstep = 1,
  .ywrapstep = 0,
  .accel = FB_ACCEL_NONE
};
 
static void ra8875_send_data(unsigned int val)
{
//  iowrite32(0xff & (val >> 8), am335x_fb_reg_base + LIDD_CS0_DATA);
  iowrite32(0xffff & val, am335x_fb_reg_base + LIDD_CS0_DATA);
}
  
static void ra8875_send_command(unsigned int val)
{
//  iowrite32(0xff & (val >> 8), am335x_fb_reg_base + LIDD_CS0_ADDR);
  iowrite32(0xffff & val, am335x_fb_reg_base + LIDD_CS0_ADDR);
}
  


/* following are the sysfs callback functions */
static ssize_t ra8875_write_cmd(struct device *dev, struct device_attribute *attr, char *buf)
{
	s32 result=0;


	return result;
}
static DEVICE_ATTR(wcmd, S_IWUSR, ra8875_write_cmd, NULL);

static ssize_t ra8875_write_dat(struct device *dev, struct device_attribute *attr, char *buf)
{
	s32 result=0;
	


	return result;
}
static DEVICE_ATTR(wdat, S_IWUSR, ra8875_write_dat, NULL);


static struct attribute *ra8875_attributes[] = {
	&dev_attr_wcmd.attr,
	&dev_attr_wdat.attr,
	NULL
};

static const struct attribute_group ra8875_attr_group = {
	.attrs = ra8875_attributes,
};



static void ra8875_send_register(unsigned int cmd, unsigned int data)
{
  ra8875_send_command(cmd);
  ra8875_send_data(data);
}
  
static void ra8875_init(void)
{
  printk("RA8875xxx%s, ++\n", __func__);
  gpio_set_value(ILI9335_SLCD_RST, 1);
  mdelay(100);
  gpio_set_value(ILI9335_SLCD_RST, 0);
  mdelay(100);  
  gpio_set_value(ILI9335_SLCD_RST, 1);
  mdelay(100);
  
  ra8875_send_register(0x0001, 0x0100);
  ra8875_send_register(0x0002, 0x0200);
  ra8875_send_register(0x0003, 0x1018);
  ra8875_send_register(0x0008, 0x0202);
  ra8875_send_register(0x0009, 0x0000);
  ra8875_send_register(0x000A, 0x0000);
  ra8875_send_register(0x000C, 0x0000);
  ra8875_send_register(0x000D, 0x0000);
  ra8875_send_register(0x0060, 0x2700);  
  ra8875_send_register(0x0061, 0x0000);
  ra8875_send_register(0x006A, 0x0000);
  mdelay(10);
  ra8875_send_register(0x0010, 0x1490);
  ra8875_send_register(0x0011, 0x0227);
  mdelay(80);
  ra8875_send_register(0x0012, 0x000c);
  mdelay(10);
  ra8875_send_register(0x0013, 0x1000);
  ra8875_send_register(0x0029, 0x000b);
  ra8875_send_register(0x002b, 0x000b);
  mdelay(10);
  ra8875_send_register(0x0020, 0x0000);
  ra8875_send_register(0x0021, 0x0000);
    
  ra8875_send_register(0x0030, 0x0000);
  ra8875_send_register(0x0031, 0x0406);
  ra8875_send_register(0x0032, 0x0002);
  ra8875_send_register(0x0035, 0x0402);
  ra8875_send_register(0x0036, 0x0004);
  ra8875_send_register(0x0037, 0x0507);
  ra8875_send_register(0x0038, 0x0103);
  ra8875_send_register(0x0039, 0x0707);
  ra8875_send_register(0x003c, 0x0204);
  ra8875_send_register(0x003d, 0x0004);
    
  ra8875_send_register(0x0050, 0x0000);
  ra8875_send_register(0x0051, 0x00ef);
  ra8875_send_register(0x0052, 0x0000);
  ra8875_send_register(0x0053, 0x013f);
  
  mdelay(10);
  ra8875_send_register(0x0007, 0x0133);  
  ra8875_send_command(0x22);
  printk("%s, --\n", __func__);
}
 
#define CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF - (val)) >> 16)
static int fb_setcolreg(unsigned regno, unsigned red, unsigned green, unsigned blue, unsigned transp, struct fb_info *info)
{
  u_short pal;
  int update_hw = 0;
  struct am335x_fb_par *par = info->par;
  unsigned short *palette = (unsigned short*) par->v_palette_base;
 
  if(regno > 255){
    return 1;
  }
 
  if(info->fix.visual == FB_VISUAL_DIRECTCOLOR){
    return 1;
  }
 
  if(info->var.bits_per_pixel > 16){
    return -EINVAL;
  }
 
  switch(info->fix.visual){
  case FB_VISUAL_TRUECOLOR:
    red = CNVT_TOHW(red, info->var.red.length);
    blue = CNVT_TOHW(blue, info->var.blue.length);
    green = CNVT_TOHW(green, info->var.green.length);
    break;
  case FB_VISUAL_PSEUDOCOLOR:
    switch(info->var.bits_per_pixel){
    case 4:
      if(regno > 15){
        return -EINVAL;
      }
 
      if(info->var.grayscale){
        pal = regno;
      } 
      else{
        red >>= 4;
        green >>= 8;
        blue >>= 12;
 
        pal = red & 0x0f00;
        pal|= green & 0x00f0;
        pal|= blue & 0x000f;
      }
 
      if(regno == 0){
        pal |= 0x2000;
      }
      palette[regno] = pal;
      break;
 
    case 8:
      red >>= 4;
      blue >>= 12;
      green >>= 8;
 
      pal = (red & 0x0f00);
      pal|= (green & 0x00f0);
      pal|= (blue & 0x000f);
 
      if(palette[regno] != pal){
        update_hw = 1;
        palette[regno] = pal;
      }
      break;
    }
    break;
  }
 
  // Truecolor has hardware independent palette
  if(info->fix.visual == FB_VISUAL_TRUECOLOR){
    u32 v;
 
    if(regno > 15){
      return -EINVAL;
    }
 
    v = (red << info->var.red.offset) | (green << info->var.green.offset) | (blue << info->var.blue.offset);
    switch(info->var.bits_per_pixel){
    case 16:
      ((u16*)(info->pseudo_palette))[regno] = v;
      break;
    case 24:
    case 32:
      ((u32*)(info->pseudo_palette))[regno] = v;
      break;
    }
    if(palette[0] != 0x4000){
      update_hw = 1;
      palette[0] = 0x4000;
    }
  }
  return 0;
}
#undef CNVT_TOHW
 
static int fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
  int err = 0;
  int bpp = var->bits_per_pixel >> 3;
  struct am335x_fb_par *par = info->par;
  unsigned long line_size = var->xres_virtual * bpp;
 
  if(var->bits_per_pixel > 16){
    return -EINVAL;
  }
 
  printk("%s, xres:%d, yres:%d, bpp:%d\n", __func__, var->xres, var->yres, var->bits_per_pixel);
  switch(var->bits_per_pixel){
  case 1:
  case 8:
    var->red.offset = 0;
    var->red.length = 8;
    var->green.offset = 0;
    var->green.length = 8;
    var->blue.offset = 0;
    var->blue.length = 8;
    var->transp.offset = 0;
    var->transp.length = 0;
    var->nonstd = 0;
    break;
  case 4:
    var->red.offset = 0;
    var->red.length = 4;
    var->green.offset = 0;
    var->green.length = 4;
    var->blue.offset = 0;
    var->blue.length = 4;
    var->transp.offset = 0;
    var->transp.length = 0;
    var->nonstd = FB_NONSTD_REV_PIX_IN_B;
    break;
  case 16:
    var->red.offset = 11;
    var->red.length = 5;
    var->green.offset = 5;
    var->green.length = 6;
    var->blue.offset = 0;
    var->blue.length = 5;
    var->transp.offset = 0;
    var->transp.length = 0;
    var->nonstd = 0;
    break;
  case 24:
    var->red.offset = 16;
    var->red.length = 8;
    var->green.offset = 8;
    var->green.length = 8;
    var->blue.offset = 0;
    var->blue.length = 8;
    var->nonstd = 0;
    break;
  case 32:
    var->transp.offset = 24;
    var->transp.length = 8;
    var->red.offset = 16;
    var->red.length = 8;
    var->green.offset = 8;
    var->green.length = 8;
    var->blue.offset = 0;
    var->blue.length = 8;
    var->nonstd = 0;
    break;
  default:
    err = -EINVAL;
  }
 
  var->red.msb_right = 0;
  var->green.msb_right = 0;
  var->blue.msb_right = 0;
  var->transp.msb_right = 0;
  if(line_size * var->yres_virtual > par->vram_size){
    var->yres_virtual = par->vram_size / line_size;
  }
  if(var->yres > var->yres_virtual){
    var->yres = var->yres_virtual;
  }
  if(var->xres > var->xres_virtual){
    var->xres = var->xres_virtual;
  }
  if(var->xres + var->xoffset > var->xres_virtual){
    var->xoffset = var->xres_virtual - var->xres;
  }
  if(var->yres + var->yoffset > var->yres_virtual){
    var->yoffset = var->yres_virtual - var->yres;
  }
  return err;
}
 
static int fb_remove(struct platform_device *dev)
{
  struct fb_info *info = dev_get_drvdata(&dev->dev);
 
  if(info){
    struct am335x_fb_par *par = info->par;
    unregister_framebuffer(info);
    fb_dealloc_cmap(&info->cmap);
    dma_free_coherent(NULL, PALETTE_SIZE, par->v_palette_base, par->p_palette_base);
    dma_free_coherent(NULL, par->vram_size, par->vram_virt, par->vram_phys);
    dma_free_coherent(NULL, par->lram_size, par->lram_virt, par->lram_phys);
    pm_runtime_put_sync(&dev->dev);
    pm_runtime_disable(&dev->dev);
    framebuffer_release(info);
  }
  return 0;
}
 
static int am335xfb_set_par(struct fb_info *info)
{
  struct am335x_fb_par *par = info->par;
   
  fb_var_to_videomode(&par->mode, &info->var);
  printk("%s, xres:%d, yres:%d, bpp:%d\n", __func__, info->var.xres, info->var.yres, info->var.bits_per_pixel);
 
  par->bpp = info->var.bits_per_pixel;
  info->fix.visual = (par->bpp <= 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
  info->fix.line_length = (par->mode.xres * par->bpp) / 8;
  par->dma_start = info->fix.smem_start + info->var.yoffset * info->fix.line_length + info->var.xoffset * info->var.bits_per_pixel / 8;
  par->dma_end = par->dma_start + info->var.yres * info->fix.line_length - 1;
  return 0;
}
 
static struct fb_ops am335x_fb_ops = {
  .owner = THIS_MODULE,
  .fb_check_var = fb_check_var,
  .fb_set_par = am335xfb_set_par,
  .fb_setcolreg = fb_setcolreg,
  .fb_fillrect = cfb_fillrect,
  .fb_copyarea = cfb_copyarea,
  .fb_imageblit = cfb_imageblit,
};
 
static irqreturn_t lcdc_irq_handler(int irq, void *arg)
{
  unsigned int stat=0;
  struct am335x_fb_par *par = (struct am335x_fb_par*)arg;
 
  stat = ioread32(am335x_fb_reg_base + IRQSTATUS);
  printk("fb stat = 0x%x\n",stat);

  if((stat & 0x04) || (stat & 0x20)) {
    printk("%s, LCDC sync lost or underflow error occured\nNot sure what to do...\n", __func__);
    iowrite32(stat, am335x_fb_reg_base + IRQSTATUS);
  }
  else{
    iowrite32(0x00000003, am335x_fb_reg_base + LIDD_CTRL);
    iowrite32(stat, am335x_fb_reg_base + IRQSTATUS);
    ra8875_send_command(0x22);
    {
      unsigned long i, num=800*480;
      uint16_t *src = par->vram_virt;
      uint16_t *dst = par->lram_virt;
      for(i=0; i<num; i++){
	ra8875_send_data(src++);
//        *dst++ = 0xff & (*src >> 8);
//        *dst++ = 0xff & (*src >> 0);
//        src+= 1;
      }
    }
    iowrite32(0x00000103, am335x_fb_reg_base + LIDD_CTRL);
  }
  return IRQ_HANDLED;
}
 
static int fb_probe(struct platform_device *device)
{
  int ret;
  unsigned long ulcm;
  struct am335x_lcdc_platform_data *fb_pdata = device->dev.platform_data;
  struct fb_videomode *lcdc_info;
  struct fb_info *am335x_fb_info;
  struct clk *fb_clk = NULL;
  struct am335x_fb_par *par;
 
  printk("RA8875 %s, ++\n", __func__);
  if((fb_pdata == NULL) && (!device->dev.of_node)){
    dev_err(&device->dev, "can not get platform data\n");
    return -ENOENT;
  }
 
  lcdc_info = devm_kzalloc(&device->dev, sizeof(struct fb_videomode), GFP_KERNEL);
  if(lcdc_info == NULL){
    return -ENODEV;
  }
  lcdc_info->name = "am335x-fb";
  lcdc_info->xres = 800;
  lcdc_info->yres = 480;
  lcdc_info->vmode = FB_VMODE_NONINTERLACED;
  lcdc_regs = platform_get_resource(device, IORESOURCE_MEM, 0);
  am335x_fb_reg_base = devm_ioremap_resource(&device->dev, lcdc_regs);
  if(!am335x_fb_reg_base){
    dev_err(&device->dev, "memory resource setup failed\n");
    return -EADDRNOTAVAIL;
  }
 
  fb_clk = devm_clk_get(&device->dev, "fck");
  if(IS_ERR(fb_clk)){
    dev_err(&device->dev, "can not get device clock\n");
    return -ENODEV;
  }
  ret = clk_set_rate(fb_clk, 100000000);
  if(IS_ERR(fb_clk)){
    dev_err(&device->dev, "can not set device clock\n");
    return -ENODEV;
  }
  pm_runtime_enable(&device->dev);
  pm_runtime_get_sync(&device->dev);
   
  printk("%s, lidd pid: 0x%x, @0x%x\n", __func__, ioread32(am335x_fb_reg_base + PID), am335x_fb_reg_base);
//  iowrite32(0x00000007, am335x_fb_reg_base + CLKC_ENABLE);
//  iowrite32(0x00000400, am335x_fb_reg_base + CTRL); // 100MHz/4
//  iowrite32(0x00000003, am335x_fb_reg_base + LIDD_CTRL); // LiDD
//  iowrite32(0x08221044, am335x_fb_reg_base + LIDD_CS0_CONF);
//  do_request(ILI9335_SLCD_RST, "slcd_reset");
  
  am335x_fb_info = framebuffer_alloc(sizeof(struct am335x_fb_par), &device->dev);
  if(!am335x_fb_info){
    dev_dbg(&device->dev, "memory allocation failed for fb_info\n");
    ret = -ENOMEM;
    goto err_pm_runtime_disable;
  }
 
  par = am335x_fb_info->par;
  par->dev = &device->dev;
  par->bpp = 16;
   
  fb_videomode_to_var(&am335x_fb_var, lcdc_info);
// ra8875_init();	//uboot already init
  printk("%s, xres: %d, yres:%d, bpp:%d\n", __func__, lcdc_info->xres, lcdc_info->yres, par->bpp);
 
/* Register sysfs hooks */
//	ret = sysfs_create_group(&device->dev.kobj, &ra8875_attr_group);
//	if (ret) {
//		dev_err(&device->dev, "registering with sysfs failed!\n");
//		goto err_release_fb;
//	}

  // allocate frame buffer
  par->vram_size = lcdc_info->xres * lcdc_info->yres * par->bpp;
  ulcm = lcm((lcdc_info->xres * par->bpp)/8, PAGE_SIZE);
  par->vram_size = roundup(par->vram_size/8, ulcm);
  par->vram_size = par->vram_size;
  par->vram_virt = dma_alloc_coherent(NULL, par->vram_size, (resource_size_t*) &par->vram_phys, GFP_KERNEL | GFP_DMA);
  if(!par->vram_virt){
    dev_err(&device->dev, "GLCD: kmalloc for frame buffer(ram) failed\n");
    ret = -EINVAL;
    goto err_release_fb;
  }
 
  par->lram_size = (lcdc_info->xres * lcdc_info->yres * 2 * 2); // fixed size for ili9335 panel
  par->lram_virt = dma_alloc_coherent(NULL, par->lram_size, (resource_size_t*) &par->lram_phys, GFP_KERNEL | GFP_DMA);
  if(!par->lram_virt){
    dev_err(&device->dev, "GLCD: kmalloc for frame buffer(slcd) failed\n");
    ret = -EINVAL;
    goto err_release_fb;
  }
  printk("vram_virt add=0x%x, smem_start=0x%x, size=%d\n",par->vram_virt, par->vram_phys, par->vram_size);
  printk("lram_virt add=0x%x,  dma_start=0x%x, size=%d\n",par->lram_virt, par->vram_phys, par->lram_size);	
  memset(par->lram_virt, 0, par->lram_size);
  am335x_fb_info->screen_base = (char __iomem*) par->vram_virt;
  am335x_fb_fix.smem_start    = par->vram_phys;
  am335x_fb_fix.smem_len      = par->vram_size;
  am335x_fb_fix.line_length   = (lcdc_info->xres * par->bpp) / 8;
 
  par->dma_start = par->vram_phys;
  par->dma_end = par->dma_start + par->vram_size - 1;
 
  // allocate palette buffer
  par->v_palette_base = dma_alloc_coherent(NULL, PALETTE_SIZE, (resource_size_t*) &par->p_palette_base, GFP_KERNEL | GFP_DMA);
  if(!par->v_palette_base){
    dev_err(&device->dev, "GLCD: kmalloc for palette buffer failed\n");
    ret = -EINVAL;
    goto err_release_fb_mem;
  }
  memset(par->v_palette_base, 0, PALETTE_SIZE);
 
  par->irq = platform_get_irq(device, 0);
  if(par->irq < 0){
    ret = -ENOENT;
    goto err_release_pl_mem;
  }
 
  am335x_fb_var.grayscale = 0;
  am335x_fb_var.bits_per_pixel = par->bpp;
 
  // Initialize fbinfo
  am335x_fb_info->flags = FBINFO_FLAG_DEFAULT;
  am335x_fb_info->fix = am335x_fb_fix;
  am335x_fb_info->var = am335x_fb_var;
  am335x_fb_info->fbops = &am335x_fb_ops;
  am335x_fb_info->pseudo_palette = par->pseudo_palette;
  am335x_fb_info->fix.visual = (am335x_fb_info->var.bits_per_pixel <= 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
 
  ret = fb_alloc_cmap(&am335x_fb_info->cmap, PALETTE_SIZE, 0);
  if(ret){
    goto err_release_pl_mem;
  }
  am335x_fb_info->cmap.len = 32;
 
  // initialize var_screeninfo
  am335x_fb_var.activate = FB_ACTIVATE_FORCE;
  fb_set_var(am335x_fb_info, &am335x_fb_var);
  dev_set_drvdata(&device->dev, am335x_fb_info);
 
  // Register the Frame Buffer
  if(register_framebuffer(am335x_fb_info) < 0){
    dev_err(&device->dev, "GLCD: Frame Buffer Registration Failed!\n");
    ret = -EINVAL;
    goto err_dealloc_cmap;
  }
 
  // setting AM335X LCDC register
  iowrite32(0x00000010, am335x_fb_reg_base + LCDDMA_CTRL); // Burst=2, 1 frame
  iowrite32(0x00000025, am335x_fb_reg_base + IRQENABLE_SET);
  iowrite32(par->lram_phys, am335x_fb_reg_base + LCDDMA_FB0_BASE);
  iowrite32(par->lram_phys + par->lram_size - 1, am335x_fb_reg_base + LCDDMA_FB0_CEILING);
  ret = devm_request_irq(&device->dev, par->irq, lcdc_irq_handler, 0, DRIVER_NAME, par);
  if(ret){
    dev_err(&device->dev, "GLCD: Frame Buffer Registration Failed(request error)!\n");
    goto irq_freq;
  }
  iowrite32(0x00000103, am335x_fb_reg_base + LIDD_CTRL); // 8080 Interface, DMA
   
  fb_prepare_logo(am335x_fb_info, 0);
  fb_show_logo(am335x_fb_info, 0);
 
  printk("%s, --\n", __func__);
  return 0;
 
irq_freq:
  unregister_framebuffer(am335x_fb_info);
 
err_dealloc_cmap:
  fb_dealloc_cmap(&am335x_fb_info->cmap);
 
err_release_pl_mem:
  dma_free_coherent(NULL, PALETTE_SIZE, par->v_palette_base, par->p_palette_base);
 
err_release_fb_mem:
  dma_free_coherent(NULL, par->vram_size, par->vram_virt, par->vram_phys);
 
err_release_fb:
  framebuffer_release(am335x_fb_info);
 
err_pm_runtime_disable:
  pm_runtime_put_sync(&device->dev);
  pm_runtime_disable(&device->dev);
 
  return ret;
}
 
#ifdef CONFIG_PM
static int fb_suspend(struct platform_device *dev, pm_message_t state)
{
  struct fb_info *info = platform_get_drvdata(dev);
 
  console_lock();
  fb_set_suspend(info, 1);
  pm_runtime_put_sync(&dev->dev);
  console_unlock();
  return 0;
}
 
static int fb_resume(struct platform_device *dev)
{
  struct fb_info *info = platform_get_drvdata(dev);
 
  console_lock();
  pm_runtime_get_sync(&dev->dev);
  fb_set_suspend(info, 0);
  console_unlock();
  return 0;
}
 
#else
 
#define fb_suspend NULL
#define fb_resume NULL
 
#endif
 
static const struct of_device_id am335x_fb_of_match[] = {
  {.compatible = "ti,am335x-lcdc", },
  {},
};
MODULE_DEVICE_TABLE(of, am335x_fb_of_match);
 
static struct platform_driver am335x_fb_driver = {
  .probe = fb_probe,
  .remove = fb_remove,
  .suspend = fb_suspend,
  .resume = fb_resume,
  .driver = {
    .name = DRIVER_NAME,
    .owner = THIS_MODULE,
    .of_match_table = of_match_ptr(am335x_fb_of_match),
  },
};
 
static int __init am335x_fb_init(void)
{
  return platform_driver_register(&am335x_fb_driver);
}
 
static void __exit am335x_fb_cleanup(void)
{
  platform_driver_unregister(&am335x_fb_driver);
}
 
module_init(am335x_fb_init);
module_exit(am335x_fb_cleanup);
 
MODULE_DESCRIPTION("AM335x framebuffer driver for RA8875 LCD panel");
MODULE_AUTHOR("Eason Chen <easonchen@eecgroup.com.tw>");
MODULE_LICENSE("GPL");
