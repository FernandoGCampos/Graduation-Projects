import numpy as np
from abc import ABC, abstractmethod

X = np.vstack([np.random.normal(1, 0.5, (100, 2)),
               np.random.normal(-2, 1, (100, 2)),
               np.random.normal(3, 0.75, (100, 2))])

y = np.hstack([np.zeros(100, dtype=int),
               np.ones(100, dtype=int),
               np.ones(100, dtype=int) + 1])

def shuffle_data(X: np.ndarray, y: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    permutation_index = np.random.permutation(X.shape[0])
    return X[permutation_index], y[permutation_index]

def filter_data(X: np.ndarray, y: np.ndarray, percentage: float) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    n_train = np.int32(percentage * X.shape[0])

    X_train = X[:n_train]
    y_train = y[:n_train]

    X_test = X[n_train:]
    y_test = y[n_train:]

    return X_train, y_train, X_test, y_test

def one_hot(y: np.ndarray) -> np.ndarray:
    unique_values = np.unique(y)
    one_hot_y = np.zeros((y.size, len(unique_values)))
    for i, (value) in enumerate(unique_values):
        one_hot_y[(y == value), i] = 1

    return one_hot_y

y = one_hot(y)

X, y = shuffle_data(X, y)
X_train, y_train, X_test, y_test = filter_data(X, y, 0.8)

class Loss(ABC):
    @abstractmethod
    def __call__(self, y_hat: np.ndarray, y: np.ndarray) -> float:
        pass

    @abstractmethod
    def deriv(self, y_hat: np.ndarray, y: np.ndarray) -> np.ndarray:
        pass

class MSE(Loss):
    def __call__(self, y_hat: np.ndarray, y: np.ndarray) -> float:
        return np.mean(np.square(y_hat - y))

    def deriv(self, y_hat: np.ndarray, y: np.ndarray) -> np.ndarray:
        return 2 * (y_hat - y)

class Activation(ABC):
    @abstractmethod
    def __call__(self, X: np.ndarray) -> np.ndarray:
        pass

    @abstractmethod
    def deriv(self, X: np.ndarray) -> np.ndarray:
        pass

class ReLU(Activation):
    def __init__(self, alpha: float = 0):
        self.alpha = alpha

    def __call__(self, X: np.ndarray) -> np.ndarray:
        y = X
        y[y < 0] *= self.alpha
        return y

    def deriv(self, X: np.ndarray) -> np.ndarray:
        y = np.ones(X.shape)
        y[X <= 0] = self.alpha
        return y

class Sigmoid(Activation):
    def __call__(self, X: np.ndarray) -> np.ndarray:
        return 1 / (1 + np.exp(-X))

    def deriv(self, X: np.ndarray) -> np.ndarray:
        f = self(X)
        return f * (1 - f)

class Softmax(Activation):
    def __call__(self, X: np.ndarray) -> np.ndarray:
        exp = np.exp(X.T)
        return (exp / np.sum(exp, axis = 0)).T

    def deriv(self, X: np.ndarray) -> np.ndarray:
        raise NotImplementedError("Softmax derivative wasn't implemented. This function can only be used in the last layer of a neural network.")

class Layer(ABC):
    @abstractmethod
    def __init__(self, input_size: int, output_size: int, activation: Activation):
        self.weights = np.random.rand(input_size, output_size) - 0.5
        self.bias = np.random.rand(1, output_size) - 0.5

        self.activation = activation

    @abstractmethod
    def __call__(self, X: np.ndarray) -> np.ndarray:
        pass

    @abstractmethod
    def forward(self, X: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
        pass

class Dense(Layer):
    def __init__(self, input_size: int, output_size: int, activation: Activation):
        self.weights = np.random.rand(input_size, output_size) - 0.5
        self.bias = np.random.rand(1, output_size) - 0.5

        self.activation = activation

    def __call__(self, X: np.ndarray) -> np.ndarray:
        return self.activation(np.dot(X, self.weights) + self.bias)

    def forward(self, X: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
        output_values = np.dot(X, self.weights) + self.bias
        activation_values = self.activation(output_values)
        return output_values, activation_values

class Model:
    def __init__(self, input_size: int, loss: Loss, lr: float = 0.01):
        self.lr = lr

        self.loss = loss

        self.last_layer_size = input_size
        self.layers: list[Layer] = []

    def add(self, layer_size: int, layer_constructor: type[Layer], activation: Activation) -> None:
        self.layers.append(layer_constructor(self.last_layer_size, layer_size, activation))
        self.last_layer_size = layer_size

    def predict(self, X: np.ndarray) -> np.ndarray:
        y = X
        for layer in self.layers:
            y = layer(y)
        return y

    def __call__(self, X: np.ndarray) -> np.ndarray:
        return self.predict(X)

    def _forward(self, X: np.ndarray) -> tuple[list[np.ndarray], list[np.ndarray]]:
        outputs = []
        activations = [X]

        cur_X = X
        for layer in self.layers:
            output_values, activation_values = layer.forward(cur_X)
            outputs.append(output_values)
            activations.append(activation_values)
            cur_X = activation_values

        return outputs, activations

    def _backward(self, X: np.ndarray, y: np.ndarray, outputs: list[np.ndarray], activations: list[np.ndarray]):
        n = y.size

        delta = self.loss.deriv(activations[-1], y)

        prev_weights = self.layers[-1].weights
        self.layers[-1].weights -= self.lr * (np.dot(activations[-2].T, delta) / n)
        self.layers[-1].bias -= self.lr * (np.sum(delta, axis=0) / n)

        for i in reversed(range(len(self.layers) - 1)):
            delta = np.dot(delta, prev_weights.T) * self.layers[i].activation.deriv(outputs[i])

            prev_weights = self.layers[i].weights
            self.layers[i].weights -= self.lr * (np.dot(activations[i].T, delta) / n)
            self.layers[i].bias -= self.lr * (np.sum(delta, axis=0) / n)


    def fit(self, X: np.ndarray, y: np.ndarray, epochs: int):
        y_pred: np.ndarray = np.argmax(y, axis = 1)
        for i in range(epochs):
            outputs, activations = self._forward(X)
            self._backward(X, y, outputs, activations)

            if (i % 10) == 0:
                print("Epoch:", i)
                y_hat = activations[-1]
                y_hat_pred = np.argmax(y_hat, axis=1)
                print("Loss: ", self.loss(y_hat, y))
                print("Acc: ", np.sum(y_pred == y_hat_pred) / y_pred.size)


model = Model(2, loss=MSE(), lr=0.05)
#model.add(10, layer_constructor=Dense, activation=Sigmoid())
model.add(10, layer_constructor=Dense, activation=ReLU(alpha = 0.3))
model.add(3, layer_constructor=Dense, activation=Softmax())

model.fit(X_train, y_train, epochs = 200)