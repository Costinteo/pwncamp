#!/usr/bin/env bash
# Script for setting up the environment 
# on a fresh virtual machine

install() {
	[ "$UID" -ne 0 ] && echo "You must be root to run this script!" && exit 1
	[ "$(echo $PWD | sed -nr 's|.+/||p')" != "pwncamp" ] && echo "You must clone pwncamp and be in its root dir!" && exit 1
	make
	local levels=$(ls bin)
	local prev_level="n00b"
	useradd "n00b" -p "#getg00d#"
	for level in $levels
	do
		grep "$level" /etc/passwd -q
		[ $? -eq 0 ] && echo "User $level already exists!" && exit 1
		local password=$(cat "./rsrc/$level/pass.txt" | cut -d : -f 2)
		useradd "$level" -p "$password" -m -s "/bin/bash"
		cp -r "./rsrc/$level/*" "/home/$level/"
		# owning
		chown "$level:$prev_level" "/home/$level/*"
		# perms
		chmod 400 "/home/$level/*"
		chmod 550 "/home/$level/$level"
		# suid
		chmod u+s "/home/$level/$level"
		prev_level=$level
	done
}

install "$@"
