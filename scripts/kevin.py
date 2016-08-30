class MyClass(object):
    """A simple example class"""

    def __init__(self):
        self.i = 12345;

    def f(self):
        return 'hello world'

    def inc(self, num):
        self.i += num      

if __name__ == '__main__':
    m = MyClass
    print(m.i)
