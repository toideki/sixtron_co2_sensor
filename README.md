commadnd to execute


'''
alias mbed_venv='python -m venv mbed_virtual'
alias mbed_source='source mbed_virtual/bin/activate'
alias mbed_target_toolchain='mbed target ZEST_CORE_FMLR-72 && mbed toolchain GCC_ARM>
alias mbed_setup='cd ~/annee_3/mbed_sensor/mbed-os-example-blinky/ && mbed_target_toolchain>
alias mbed_compile='mbed compile'
alias mbed_flash='sixtron_flash'
alias mbed_minicom='minicom -b 9600 -D'
'''



mbed new .
mbed config root .
mbed add mbed-os
mbed import mbed-os
mbed target ZEST_CORE_FMLR-72 && mbed toolchain GCC_ARM

if pc is not compatible, use a python virtual env
python3 -m venv mbed_virtual
source mbed_virtual/bin/activate
pip install mbed-cli
pip install setuptools -> if ModuleNotFoundError: No module named 'distutils'
pip install --upgrade six -> if [ERROR] No module named 'six.moves'


if we still lack 
cd mbed-os
pip install -r requirements.txt
