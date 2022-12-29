# ----------------------
# - read the input data:

import mnist_loader
import sys
training_data, validation_data, test_data = mnist_loader.load_data_wrapper()
training_data = list(training_data)
test_data = list(test_data)

# sys.stdout = open("image_data.txt", "w")
# print("array for image")
# print(list(validation_data)[4])
# sys.stdout.close()


# ----------------------
# - run the network with SGD training

import network
net = network.Network([784, 30, 10])
net.SGD(training_data, 30, 10, 3.0, test_data=test_data) #eta is the learning rate
