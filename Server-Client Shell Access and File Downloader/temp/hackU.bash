#/bin/hash
###########################################################################################################

DATE=`/bin/date +date_%d-%m-%y_time_%H-%M-%S`
Time(){

###### STARTING PROGRAMMING AND TYPING THE USER INTERFACE ##########
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
echo ""
echo " Computer Time : `date` "
echo ""
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
########### START SCRIPT MAIN PROGRAMMING AND COMMANDS WRITING #####################
}
GenInfo(){
## --------------------------------------<General Infromation>-----------------------------------##
echo "___________________________________________________________________________________"
echo "**** General Information About This Computer ****"
echo "___________________________________________________________________________________"
echo "This Computer Using `uname -m` architecture ;"
echo "The Linux Kernel Used on this computer `uname -r`"
echo -e "This Linux Distro. Used On this computer `head -n1 /etc/issue`"
echo "The Host Name Of this computer is `hostname`"
echo "The Name Of the user Of this computer is `whoami` "
echo "The Number Of The Users That Using This Computer `users | wc -w` Users "
echo "The System Uptime = `uptime | awk '{ gsub(/,/, ""); print $3 }'` (Hrs:Min)"
echo "The Run level Of Current OS is `runlevel`"
echo "The Number OF Running Process :`ps ax | wc -l`"
echo "___________________________________________________________________________________"
## --------------------------------------<General Infromation/end>-------------------------------##
}

CPUInfo(){ ## --------------------------------------<CPU Infromation>---------------------------------------##
echo "___________________________________________________________________________________"
echo "****The CPU Infromation****"
echo "___________________________________________________________________________________"
echo "You Have `grep -c 'processor' /proc/cpuinfo` CPU"
echo "Your CPU model name is `awk -F':' '/^model name/ { print $2 }' /proc/cpuinfo`"
echo "Your CPU vendor`awk -F':' '/^vendor_id/ { print $2 }' /proc/cpuinfo`"
echo "Your CPU Speed`awk -F':' '/^cpu MHz/ { print $2 }' /proc/cpuinfo`"
echo "Your CPU Cache Size`awk -F':' '/^cache size/ { print $2 }' /proc/cpuinfo`"
echo "___________________________________________________________________________________"

## --------------------------------------<CPU Infomation/end>-----------------------------------##

}

MemInfo(){
## --------------------------------------<memory Information>------------------------------------##
echo "___________________________________________________________________________________"
echo " ****The Memory Information****"
echo "___________________________________________________________________________________"
echo "`cat /proc/meminfo`"
echo "___________________________________________________________________________________"
echo "`free -m`"
echo "___________________________________________________________________________________"

## --------------------------------------<memory Infromation/end>--------------------------------##
}

FileSInfo(){

## --------------------------------------<File Systems Infromation>-------------------------------##
echo "___________________________________________________________________________________"
echo "*****File Systems Infromation******"
echo "___________________________________________________________________________________"
echo "`df -h`"
echo "___________________________________________________________________________________"

## --------------------------------------<File Systems Infromation/end>------------------------------##
}

PCIInfo(){
## --------------------------------------<Pci Devices Information script>-------------------------##
echo "___________________________________________________________________________________"
echo "******PCI devices On MOtherboard information {detailed}******"
echo "___________________________________________________________________________________"
echo "`lspci -tv`"
echo "___________________________________________________________________________________"
## --------------------------------------<Pci Devices Information script/end>----------------------##

}

NetInfo(){
## --------------------------------------<Netwrok Infromation>-------------------------------------##
echo "___________________________________________________________________________________"
echo "********Network Information********"
echo "___________________________________________________________________________________"
echo "`/sbin/ifconfig`"
echo "___________________________________________________________________________________"
## --------------------------------------<network Infromation/end>--------------------------------##

}

## --------------------------------------<script ending>-----------------------------------------##

Run(){
echo "<html><body>"
Time
GenInfo
CPUInfo
MemInfo
FileSInfo
PCIInfo
NetInfo
echo "</body></html>"
}
log=Sysinfo_$DATE
Run | tee $log.txt
mv $log.txt $log.html
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
