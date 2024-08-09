from math import pi

class Figura:
    def __init__(self, cor = '', tipo = 0, filled = True):
        self.cor = cor
        self.tipo = tipo
        self.filled = filled

class retangulo(Figura):
    def __init__(self, ladoa = 0, ladob = 0, **kwargs):
        super().__init__(**kwargs, tipo = 1)
        self.ladoa = ladoa
        self.ladob = ladob

    def area(self):
        return self.ladoa * self.ladob

    def perimetro(self):
        return 2 * (self.ladoa + self.ladob)

class quadrado(Figura):
    def __init__(self, lado = 0, **kwargs):
        super().__init__(**kwargs, tipo = 2)
        self.lado = lado

    def area(self):
        return self.lado ** 2

    def perimetro(self):
        return 4 * self.lado

class circulo(Figura):
    def __init__(self, raio = 0, **kwargs):
        super().__init__(**kwargs, tipo = 3)
        self.raio = raio

    def area(self):
        return self.raio ** 2 * pi

    def perimetro(self):
        return 2 * pi * self.raio