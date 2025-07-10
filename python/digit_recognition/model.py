from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Flatten
from keras.layers import Conv2D, MaxPooling2D
from keras.utils import to_categorical
from keras.optimizers.experimental import SGD
from keras.losses import categorical_crossentropy
from keras.layers import BatchNormalization
import numpy as np
import random
# import keras
# from keras import backend as K
# import tensorflow as tf


class App():
    def __init__(self):
        self.make_file(images_per_class=10,
                       layer_config=[16, 32, 32, 50])
        self.make_file(images_per_class=10,
                       layer_config=[32, 64, 64, 100])
        self.make_file(images_per_class=10,
                       layer_config=[64, 128, 128, 200])

        self.make_file(images_per_class=50,
                       layer_config=[16, 32, 32, 50])
        self.make_file(images_per_class=50,
                       layer_config=[32, 64, 64, 100])
        self.make_file(images_per_class=50,
                       layer_config=[64, 128, 128, 200])

        self.make_file(images_per_class=100,
                       layer_config=[16, 32, 32, 50])
        self.make_file(images_per_class=100,
                       layer_config=[32, 64, 64, 100])
        self.make_file(images_per_class=100,
                       layer_config=[64, 128, 128, 200])

    def make_file(self, images_per_class, layer_config):
        self.prepare(images_per_class)
        self.model_generation(layer_config)
        layers = '+'.join([str(item) for item in layer_config])
        self.finalize(f"mnist_{images_per_class}_{layers}")

    def prepare(self, quantity_per_class):
        # devices = tf.config.list_physical_devices()
        # device_found = False
        # for device in devices:
        #     if device.name == "/device:GPU:0":
        #         print("device found: <{}>".format(device.name))
        #         device_found = True
        #         break
        #     else:
        #         print("device present: <{}>".format(device.name))
        # if not device_found:
        #     raise SystemError("selected device not found")
        # the data, split between train and test sets
        data, (x_test, y_test) = mnist.load_data()
        indices = [[] for _ in range(10)]
        for i in range(10):
            while len(indices[i]) < quantity_per_class:
                selected_index = random.randrange(len(data[1]))
                if data[1][selected_index] == i:
                    indices[i].append(selected_index)
        x_train = []
        y_train = []
        for index in [i for j in indices for i in j]:
            x_train.append(data[0][index])
            y_train.append(data[1][index])
        x_train = np.array(x_train)
        y_train = np.array(y_train)
        print(x_train.shape, y_train.shape)
        x_train = x_train.reshape(x_train.shape[0], 28, 28, 1)
        x_test = x_test.reshape(x_test.shape[0], 28, 28, 1)
        self.input_shape = (28, 28, 1)
        self.batch_size = 32
        self.epochs = 10
        # convert class vectors to binary class matrices
        y_train = to_categorical(y_train)
        y_test = to_categorical(y_test)
        x_train = x_train.astype("float32")
        x_test = x_test.astype("float32")
        x_train /= 255.0
        x_test /= 255.0
        print("x_train shape:", x_train.shape)
        print(x_train.shape[0], "train samples")
        print(x_test.shape[0], "test samples")
        self.x_train = x_train
        self.y_train = y_train
        self.x_test = x_test
        self.y_test = y_test

    def model_generation(self, layer_config):
        self.model = Sequential()
        self.model.add(Conv2D(layer_config[0], (3, 3), activation='relu',
                              kernel_initializer='he_uniform',
                              input_shape=self.input_shape))
        self.model.add(MaxPooling2D((2, 2)))
        self.model.add(Conv2D(layer_config[1], (3, 3), activation='relu',
                              kernel_initializer='he_uniform'))
        self.model.add(BatchNormalization())
        self.model.add(Conv2D(layer_config[2], (3, 3), activation='relu',
                              kernel_initializer='he_uniform'))
        self.model.add(MaxPooling2D((2, 2)))
        self.model.add(Flatten())
        self.model.add(Dense(layer_config[3], activation='relu',
                             kernel_initializer='he_uniform'))
        self.model.add(BatchNormalization())
        self.model.add(Dense(10, activation='softmax'))

    def finalize(self, model_name):
        opt = SGD(learning_rate=0.01, momentum=0.9)
        # opt=keras.optimizers.Adadelta()
        self.model.compile(optimizer=opt, loss='categorical_crossentropy',
                           metrics=["accuracy"])
        # with tf.device("/gpu:0"):
        #     model.fit(x_train, y_train, batch_size=batch_size,
        #               epochs=epochs, verbose=1, validation_data=(x_test, y_test))
        self.model.fit(self.x_train,
                       self.y_train,
                       batch_size=self.batch_size,
                       epochs=self.epochs,
                       verbose=1,
                       validation_data=(self.x_test, self.y_test))
        self.model.save(f"{model_name}.h5")
        print(f"Saving the model as {model_name}.h5")
        score = self.model.evaluate(self.x_test,
                                    self.y_test,
                                    verbose=0)
        print("Test loss:", score[0])
        print("Test accuracy:", score[1])


App()
