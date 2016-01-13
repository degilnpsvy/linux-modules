../scripts/rootfs.mount
for d in ./*
do
    if [ -d ${d} ] ; then
        sudo cp ${d}/*.ko ${TOP_DIR}/rootfs/ ;
    fi
done
../scripts/rootfs.umount
