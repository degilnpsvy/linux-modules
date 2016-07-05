obj-m += kobject.o

all:
	make -C ${LINUX_DIR} M=`pwd` O=${LINUX_BUILD_DIR} modules

install:
	make -C ${LINUX_DIR} M=`pwd` O=${LINUX_BUILD_DIR} INSTALL_MOD_PATH=${INSTALL_MODULE_DIR} modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c modules.order Module.symvers .tmp_versions
