cmd_/home/toolchains/r3.1.1/obj/linux-2015.11-32-mips-linux-gnu-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset/.install := /bin/sh scripts/headers_install.sh /home/toolchains/r3.1.1/obj/linux-2015.11-32-mips-linux-gnu-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset ./include/uapi/linux/netfilter/ipset ip_set.h ip_set_bitmap.h ip_set_hash.h ip_set_list.h; /bin/sh scripts/headers_install.sh /home/toolchains/r3.1.1/obj/linux-2015.11-32-mips-linux-gnu-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset ./include/linux/netfilter/ipset ; /bin/sh scripts/headers_install.sh /home/toolchains/r3.1.1/obj/linux-2015.11-32-mips-linux-gnu-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset ./include/generated/uapi/linux/netfilter/ipset ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/toolchains/r3.1.1/obj/linux-2015.11-32-mips-linux-gnu-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset/$$F; done; touch /home/toolchains/r3.1.1/obj/linux-2015.11-32-mips-linux-gnu-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset/.install
