#!/usr/bin/env bash
# Script for setting up the environment 
# on a fresh virtual machine

usage() {
	cat <<- _end_of_usage
	Usage: setup.sh [install|remove]
	_end_of_usage
}

make_users() {
	local levels=$(ls bin)
	local prev_level="n00b"
	useradd "n00b" -p "$(mkpasswd .getg00d!)"
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
	chmod -r /tmp
}

setup() {
	[ "$UID" -ne 0 ] && echo "You must be root to run this script!" && exit 1
	[ "$(echo $PWD | sed -nr 's|.+/||p')" != "pwncamp" ] && echo "You must clone pwncamp and be in its root dir!" && exit 1
	make
	local mode=$1
	case "$mode" in
	"install") make_users   ;;
	"remove")  remove_users ;;
	*) usage ;;
	esac
	extra
}

setup "$@"
