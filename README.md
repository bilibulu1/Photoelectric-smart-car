#YOLOV5 for Object Detection, Photoelectric-smart-car. 
Some auxiliary functions are implemented, such as clustering, dataset division, etc
##introduction
This photoelectric garbage sorting vehicle is composed of modules such as navigation unit, target recognition unit, and main control chip. The navigation unit is composed of ultrasonic sensors and Jetson Nano. Two ultrasonic modules are installed in front of the trolley, and one ultrasonic module is installed on the left and right. The first ultrasonic module in the front is installed at the pusher for measuring and garbage The second ultrasonic module in front is set on the upper side of the front of the car to measure the distance from the obstacle in front of the car. One ultrasonic wave on the left and right is used to measure the distance from the left and right borders to avoid the car going out of bounds. The target recognition module consists of It is composed of an Astra pro camera, which is responsible for identifying the type of garbage and where the garbage is placed. The main control chip is STM32F103ZET6, which is responsible for controlling the travel path of the trolley.
##Using the code for training a gargabe detector:
```python
python train.py --weights yolov5s.pt --cfg garbage.yaml --data garbage.yaml --epochs 500 --batch-size 16 --device 0 --multi-scale  --adam
```

In the Control folder, you can find the communication code between STM32 and Jetson Nano and the code for STM32 to control the car servo to control the trolley.