#!/usr/bin/env bash
# Script for setting up the environment 
# on a fresh virtual machine

# TODO:
# write a better usage
# have README/motd be a file in rsrc
# use rsrc/levels to create homes

usage() {
	cat <<- _end_of_usage
	Usage: setup.sh [install | remove]
	_end_of_usage
}

dump_readme() {
	cat <<- _end_of_readme
	    ___ _    _____  _______ ___ _  ___ 
	   / _ \\ |/|/ / _ \\/ __/ _ \`/  ' \\/ _ \\
	  / .__/__,__/_//_/\\__/\\_,_/_/_/_/ .__/
	 /_/                            /_/    
	-----------------------------------------------------------------------------
	  Welcome to the pwncamp, agent!

	  We've prepared 8 challenging levels that you can find in /home/. Each level 
	  passed will unlock the next one, by giving you the login details for it.
	 
	  Write permissions to home directories are disabled, by default. Therefore,
	  we suggest creating a hard-to-guess work directory in /tmp/. 
	  Using "mktemp -d" is recommended. The /tmp/ and /proc/ directories also 
	  do not have read permissions, so players cannot snoop on eachother.

	  Some unenforced rules:
	    > don't leave orphaned processes running
	    > don't leave exploit-files or solutions around
	    > don't annoy other players
	    > don't post spoilers

	-- TIPS --
	  Not all binaries are compiled the same way. The way a binary is compiled
	  might give away hints to how it's solved.

	  However, in the current version, the differences are small.

	-- TOOLS --
	  This machine has some tools installed, for your convenience:
	    > gef              [https://github.com/hugsy/gef]
	    > pwntools         [https://github.com/Gallopsled/pwntools]
	    > radare2          [https://github.com/radareorg/radare2]
	    > checksec         [https://github.com/slimm609/checksec.sh]

	  Other recommended tools:
	    > angr          [https://angr.io/]
	    > x64dbg        [https://github.com/x64dbg/x64dbg]
	    > shellme       [https://github.com/hatRiot/shellme]
	    > shellcode_gen [https://masterccc.github.io/tools/shellcode_gen/]

	  Other notable tools installed on linux systems:
	    > objdump
	    > Python3
	    > strace
	    > ltrace
	    > strings

	  But we strongly encourage you to use local decompilation software, such as:
	    > Ghidra [https://ghidra-sre.org/]
	    > IDA    [https://hex-rays.com/] (only PRO version has the decompiler!)
	    > Cutter [https://github.com/rizinorg/cutter]
	    > Binja  [https://binary.ninja/]
	    > etc...

	  Because they have a GUI, they would have to be installed locally.
	  You can use "scp" to download binaries locally, to your machine. 
	  Example (on your machine):
	  $ scp -P <port> <user>@<host>:/path/to/remote/src /path/to/local/dest
	
	  Don't forget that you can always develop the exploit locally and then
	  port it over to the pwncamp machine, if you prefer other tools.

	-- MORE INFORMATION --
	  This wargame (and this README) was greatly inspired by OverTheWire.
	  If you like this type of challenge, definitely check them out at:
	    > http://www.overthewire.org/wargames/

	  Also recommended:
	    > https://github.com/guyinatuxedo/nightmare
	-----------------------------------------------------------------------------
	_end_of_readme
}

make_users() {
	make
	local levels=$(ls bin)
	
	# n00bstuff
	local prev_level="n00b"
	useradd "n00b" -p "$(mkpasswd .getg00d!)" -m -d /home/n00b -s "/bin/bash"
	chmod 555 /home/n00b
	dump_readme > /home/n00b/README
	chmod 444 /home/n00b/README
	cp /home/n00b/README /etc/motd
	echo "Created user n00b!"

	for level in $levels
	do
		grep "$level" /etc/passwd -q
		[ $? -eq 0 ] && echo "User $level already exists!" && exit 1
		local password=$(cat "./rsrc/$level/pass.txt" | cut -d : -f 2)
		useradd "$level" -p "$(mkpasswd $password)" -m -d /home/$level -s "/bin/bash"
		cp -r ./rsrc/$level/* /home/$level/
		cp ./bin/$level /home/$level/
		# owning
		chown "$level:$prev_level" /home/$level/*
		# perms
		chmod 555 /home/$level
		chmod 400 /home/$level/*
		chmod 550 /home/$level/$level
		# suid
		chmod u+s /home/$level/$level
		prev_level=$level
		echo "Created user $level!"
	done
}

remove_users() {
	local levels=$(ls bin)
	userdel -r n00b
	echo "Deleted user n00b..."
	for level in $levels
	do
		userdel -r $level
		echo "Deleted user $level..."
	done
}

# setup some extra permissions
extra() {
	local no_read_perm="/tmp /proc"
	for dir in $no_read_perm
	do
		chmod -r $dir
	done
}

setup() {
	[ "$UID" -ne 0 ] && echo "You must be root to run this script!" && exit 1
	[ "$(echo $PWD | sed -nr 's|.+/||p')" != "pwncamp" ] && echo "You must clone pwncamp and be in its root dir!" && exit 1
	local mode=$1
	case "$mode" in
	"install") make_users && extra ;;
	"remove")  remove_users ;;
	*) usage ;;
	esac
}

setup "$@"
