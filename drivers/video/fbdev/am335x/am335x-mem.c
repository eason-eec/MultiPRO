#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <linux/gpio.h>

#define DEVICE_NAME "mymap"
//#define MM_SIZE (800*480*2)
//static unsigned char array[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
unsigned char *ra8875_buffer;
long MM_SIZE;

static int my_open(struct inode *inode, struct file *file)
{
        return 0;
}

static int my_map(struct file *filp, struct vm_area_struct *vma)
{
        unsigned long phys;

        //得到物理地址
        phys = virt_to_phys(ra8875_buffer);
        //将用户空间的一个vma虚拟内存区映射到以page开始的一段连续物理页面上
        if(remap_pfn_range(vma,
                        vma->vm_start,
                        phys >> PAGE_SHIFT,//第三个参数是页帧号，由物理地址右移PAGE_SHIFT得>到
                        vma->vm_end - vma->vm_start,
                        vma->vm_page_prot))
                return -1;

        return 0;
}

static struct file_operations dev_fops = {
        .owner = THIS_MODULE,
        .open = my_open,
        .mmap = my_map,
};

static struct miscdevice misc = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = DEVICE_NAME,
        .fops = &dev_fops,
};

static ssize_t hwrng_attr_current_show(struct device *dev,
                                struct device_attribute *attr, char *buf)
{
        int i;

        for(i = 0; i < 10 ; i++){
                printk("%d\n", ra8875_buffer[i]);
        }

        return 0;
}
static DEVICE_ATTR(rng_current, S_IRUGO | S_IWUSR, hwrng_attr_current_show, NULL);

static int __init dev_init(void)
{
        int ret;
//        unsigned char i;

        //内存分配
        ra8875_buffer = (unsigned char *)kmalloc(MM_SIZE, GFP_KERNEL);
//       ra8875_buffer在am335x-fb.c中設定
        //driver起来时初始化内存前10个字节数据
//        for(i = 0;i < 10;i++)
//                ra8875_buffer[i] = array[i];
        //将该段内存设置为保留
        SetPageReserved(virt_to_page(ra8875_buffer));

        //注册混杂设备
        ret = misc_register(&misc);
        ret = device_create_file(misc.this_device, &dev_attr_rng_current);

        return ret;
}

static void __exit dev_exit(void)
{
        device_remove_file(misc.this_device, &dev_attr_rng_current);
        //注销设备
        misc_deregister(&misc);
        //清除保留
        ClearPageReserved(virt_to_page(ra8875_buffer));
        //释放内存
        kfree(ra8875_buffer);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("LKN@SCUT");
