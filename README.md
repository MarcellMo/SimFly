# SimFly
Arduino block driver library for autocode generation of simulink models

According to: https://de.mathworks.com/matlabcentral/fileexchange/39354-device-drivers

Download the folder and include the path in Matlab with the set path button in the environment tab. Use “add with subfolders” to automatically include all files. 

Open a new Simulink model. In the Simulink Library browser, right click and “Refresh Library Browser”. Alternatively press F5. The Library SimFLy should appear. You’re ready to use the device driver blocks. 

As the wrapper code has to be included in the specific Simulink model with the set custom source command, drag the Arduio_DUE_HAL or Arduino_Nano_HAL in the model and double-click it. Now the compiler finds the wrapper code at building time.

In the model configuration parameters in Hardware Implementation select your hardware board (Due, Nano).

Click "Build Model" and let the magic happen ;-) 
