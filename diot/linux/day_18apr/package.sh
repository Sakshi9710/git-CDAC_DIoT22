echo "Installing net-tools"
#install_tool=`sudo apt purge`
read -p "Enter package you want to install : " package
sudo apt install $package