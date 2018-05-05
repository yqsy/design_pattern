class Base(object):
    pass

class Derived(Base):
    pass



def main():
    d = Derived()
    print(type(d))
    
    d_clone = type(d)()
    print(type(d_clone))

if __name__ == '__main__':
    main()
