#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/pid.h>
#include <linux/sched.h>





static int myint = 420;
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");


static int simple_init(void) {
	struct task_struct *adar ;
	struct task_struct *myparent;
	struct task_struct *task;
	struct list_head *list;
	adar =get_pid_task(find_get_pid(myint),PIDTYPE_PID);
	myparent=adar->parent;
	printk(KERN_INFO "PARENT ID %d\n",myparent->pid);
	

	list_for_each(list, &myparent->children) {
    task = list_entry(list, struct task_struct, sibling);
    printk(KERN_INFO "siblingsPID: %d executible name: %s\n",task->pid,task->comm);
}
 
 printk(KERN_INFO "myint is an integer: %d\n", myint);
 return 0;
}
static void simple_exit(void) {

}
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
