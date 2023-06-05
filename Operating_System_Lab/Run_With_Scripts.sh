#! /bin/bash

manage_firefox () {
    killall firefox
    password_file="firefox_password.txt"  # Set the path to your password file here
    stored_password=$(cat "$password_file")
    
    if [ ! "$stored_password" ]; then
        echo "No password is set for the program."
        read -p "Do you want to run the program without a password? (y/n): " choice
        if [[ $choice =~ ^[Yy]$ ]]; then
            firefox
        else
            read -s -p "Enter the password to run the program: " new_password
            echo "$new_password" > "$password_file"
            firefox
        fi
    else
    # Password is set for the program
        read -sp "Enter the password: " entered_password

        if [ "$entered_password" == "$stored_password" ]; then
            read -p "Password correct. Do you want to set a new password? (y/n): " choice
            if [ "$choice" == "y" ]; then
                read -sp "Enter the new password: " new_password
                echo "$new_password" > "$password_file"
                echo "New password set successfully."
            fi
            firefox
        else
            echo "Incorrect password. Program cannot be run."
        fi
    fi
}


manage_gnome_calculator () {
    killall gnome-calculator
    password_file="password_gnome-calculator.txt"  # Set the path to your password file here
    stored_password=$(cat "$password_file")
    
    if [ ! "$stored_password" ]; then
        echo "No password is set for the program."
        read -p "Do you want to run the program without a password? (y/n): " choice
        if [[ $choice =~ ^[Yy]$ ]]; then
            gnome-calculator
        else
            read -s -p "Enter the password to run the program: " new_password
            echo "$new_password" > "$password_file"
            gnome-calculator
        fi
    else
    # Password is set for the program
        read -sp "Enter the password: " entered_password

        if [ "$entered_password" == "$stored_password" ]; then
            read -p "Password correct. Do you want to set a new password? (y/n): " choice
            if [ "$choice" == "y" ]; then
                read -sp "Enter the new password: " new_password
                echo "$new_password" > "$password_file"
                echo "New password set successfully."
            fi
            gnome-calculator
        else
            echo "Incorrect password. Program cannot be run."
        fi
    fi
}


while :; do
  test -n "`pgrep firefox`" && manage_firefox
  test -n "`pgrep calculator`" && manage_gnome_calculator
  sleep 1
done
