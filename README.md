# KGuard
Stack protection implemented using a modified Linux kernel

## VM Setup

For the purposes of this project, we use VirtualBox to emulate a Linux
environment. The testing environment is Ubuntu 18.04 Server. You can download
the prebuilt [VirtualBox OVA file]. This file was built using Ubuntu 18.04 Server.

You can follow the same instructions as for [Project 0], particularly those
related to networking. To allow enough memory and CPU power to compile the kernel
reasonably fast, you should additionally set the following options:
 - Under System > Motherboard, increase Base Memory to (hopefully) 4096 MB.
 - Under System > Processor, increase the number of Processors until you reach the red zone.

The disk space for the OVA file was set at 50 GB, so you should allow for that much
space.

After starting VM, log into Ubuntu using `user` as username, and `263` as password.
You should also be able to `ssh` into the VM.

## Compiling and Installing the Kernel

Clone this repository and then run `cd linux-4.17/`. First, run
~~~console
user@cs263$ cp /boot/config-$(uname -r) ../config.old
~~~
This will backup the old configuration. Then, run
~~~console
user@cs263$ sudo make olddefconfig
~~~
At this point, you will likely be prompted to install many packages. Do it. Some
of them are `bison`, `flex`, and `bc`. Possibly, you will also be asked to install
`gcc` and `make`, but these should already come with the VM image. Then, run
~~~console
user@cs263$ sudo make -j 4
~~~
This will take a while. The `-j` command sets the number of processors to be utilized
during the compilation; you should set this to the same number as the number of
processors in VM settings. In my case, with 4 processors, compilation took about
45 minutes. After the compilation is done, run
~~~console
user@cs263$ sudo make modules_install -j 4
~~~
When this is done, run finally
~~~console
user@cs263$ sudo make install -j 4
~~~
Now, reboot to apply changes. During reboot, you might see the GRUB bootloader
menu; if this is the case go to `Advanced options for Ubuntu` and pick the
`4.17` version of the kernel. Once the machine boots up, run the following
command
~~~console
user@cs263$ uname -r
~~~
If all went well, this command should output `4.17.0`. If this is not the case,
reboot again, and this time hold the shift key to force access to GRUB bootloader
menu. Then, pick the `4.17` version.

### Potential Troubleshooting

When I first did this, I set the amount of memory for my VM to 2 GB. Apparently,
this was not enough, so when I installed the kernel and rebooted, I was getting
a kernel panic because there was not enough memory.


[Project 0]: https://harvard-cs263.github.io/2021f/writeup-write-a-story.html 
[VirtualBox OVA file]: https://drive.google.com/file/d/15fDwj61TuEqDLISUiXbz5HxJoGsMoF22/view?usp=sharing

