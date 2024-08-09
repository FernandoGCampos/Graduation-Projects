import numpy as np
import matplotlib.pyplot as plt

dados = np.random.normal(1, 0.5, [100,2])
dados.shape

X = np.vstack([np.random.normal(1, 0.5, [100,2]),
                  np.random.normal(-2, 1, [100,2]),
                  np.random.normal(3, 0.75, [100,2])]
                  )
y = np.hstack([np.zeros(100, dtype=int),
               np.ones(100, dtype=int),
               np.ones(100, dtype=int) + 1])
# notação one-hot
def one_hot(y):
  one_hot_y = np.zeros((len(np.unique(y)),y.size))
  one_hot_y[y,np.arange(y.size)] = 1
  return one_hot_y

y = one_hot(y)

# sortear e dividir
ordem = np.random.permutation(X.shape[0])

n_train = int(0.8*X.shape[0])

y_train = y[:,ordem[:n_train]]
X_train = X[ordem[:n_train]]

y_test = y[:,ordem[n_train:]]
X_test = X[ordem[n_train:]]

def init_params():
  W1 = np.random.rand(2, 10) - 0.5
  b1 = np.random.rand(1, 10) - 0.5
  W2 = np.random.rand(10, 3) - 0.5
  b2 = np.random.rand(1, 3) - 0.5

  return W1, b1, W2, b2

def ativacao(Z):
  return 1 / (1 + np.exp(-Z))

def softmax(Z):
  exp = np.exp(Z)
  return exp / sum(exp)

def forward(X, W1, b1, W2, b2):
  O1 = np.dot(X, W1) + b1
  A1 = ativacao(O1)

  O2 = np.dot(A1, W2) + b2
  A2 = softmax(O2.T)

  return O1, A1, O2, A2

def deriv(Z):
  f = ativacao(Z)
  return f * (1-f)

def backward(O1, A1, O2, A2, W1, W2, X, y):
  n = y.size

  err = 2 * (A2 - y)
  dW2 = np.dot(err, A1) / n
  db2 = np.sum(err, axis=1) / n

  err1 = np.dot(W2, err) * deriv(O1.T)
  dW1 = np.dot(err1, X) / n
  db1 = np.sum(err1, axis=1) / n
  return dW1, db1, dW2, db2

def adjust_params(W1, b1, W2, b2, dW1, db1, dW2, db2, lr = 0.1):
  W1 -= lr * dW1.T
  b1 -= lr * db1.T
  W2 -= lr * dW2.T
  b2 -= lr * db2.T

  return W1, b1, W2, b2

def get_preds(y):
  return np.argmax(y, axis=0)

def get_accuracy(y_hat, y):
  return np.sum(y_hat == y) / y.size

def fit(X, y, lr = 0.01, n_epochs = 100):

  W1, b1, W2, b2 = init_params()

  for i in range(n_epochs):
    O1, A1, O2, A2 = forward(X_train, W1, b1, W2, b2)
    dW1, db1, dW2, db2 = backward(O1, A1, O2, A2, W1, W2, X_train, y_train)
    W1, b1, W2, b2 = adjust_params(W1, b1, W2, b2, dW1, db1, dW2, db2, lr=lr)
    if (i % 10 == 0):
      print("Epoch: ", i)
      y_pred = get_preds(y)
      y_hat = get_preds(A2)
      print("Loss: ", np.mean(np.square(y-A2)))
      print("Acc:", get_accuracy(y_hat, y_pred))

  return W1, b1, W2, b2

def predict(X, W1, b1, W2, b2):
  O1, A1, O2, A2 = forward(X, W1, b1, W2, b2)
  return get_preds(A2)

W1, b1, W2, b2 = fit(X_train, y_train, lr = 0.05, n_epochs = 200)
