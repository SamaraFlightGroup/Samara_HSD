# Hardware Abstraction Layer(HAL) Driver Folder
Put drivers for IMXRT1062 hardware peripheral's in this folder. 
Must use a hpp/h and cpp/c file for every driver. Must use header guards See example for details.
Remember to add each cpp/c file to the CmakeLists.txt.
## Example hpp file
```
#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

includes...

defines...

definitions...

#endif
```
## Example h file
```
#ifndef GPIO_H
#define GPIO_H

includes...

#ifdef __cplusplus
extern "C"
{
#endif

defines...

definitions...

#ifdef __cplusplus
}
#endif
#endif
```