echo "Cloning repositories..."
git clone --recursive https://github.com/sirius-johnny/2025_CAD_C.git
git clone --recursive https://github.com/The-OpenROAD-Project/OpenROAD.git

echo "Installing dependencies for OpenROAD..."
bash OpenROAD/etc/DependencyInstaller.sh -all

echo "Building OpenROAD..."
cd OpenROAD
mkdir build
cd build
cmake ..
make -j 6
cd ../../

echo "Copying OpenROAD binary..."
cp OpenROAD/build/src/openroad .

echo "Building 2025_CAD_C..."
cd 2025_CAD_C
mkdir bin
make

echo "Preparing dump lib..."
cd openroad_call
mkdir dump_for_Cplus
../../openroad -exit -python parse.py

echo "Running C++ parser..."
cd ../
./bin/cadC ./testcase/aes_cipher_top/aes_cipher_top_cell_info.csv

echo "Parser done!"

echo "Generating output files..."
cd ../
cp 2025_CAD_C/testcase/aes_cipher_top/aes_cipher_top.pl ./aes_cipher_top_updated.pl
touch aes_cipher_top.changelist