from test_support import verify, verbose, TestFailed
import sys
import gc

def expect(actual, expected, name):
    if actual != expected:
        raise TestFailed, "test_%s: actual %d, expected %d" % (
            name, actual, expected)

def expect_nonzero(actual, name):
    if actual == 0:
        raise TestFailed, "test_%s: unexpected zero" % name

def run_test(name, thunk):
    if verbose:
        print "testing %s..." % name,
    thunk()
    if verbose:
        print "ok"

def test_list():
    l = []
    l.append(l)
    gc.collect()
    del l
    expect(gc.collect(), 1, "list")

def test_dict():
    d = {}
    d[1] = d
    gc.collect()
    del d
    expect(gc.collect(), 1, "dict")

def test_tuple():
    # since tuples are immutable we close the loop with a list
    l = []
    t = (l,)
    l.append(t)
    gc.collect()
    del t
    del l
    expect(gc.collect(), 2, "tuple")

def test_class():
    class A:
        pass
    A.a = A
    gc.collect()
    del A
    expect_nonzero(gc.collect(), "class")

def test_newstyleclass():
    class A(object):
        pass
    gc.collect()
    del A
    expect_nonzero(gc.collect(), "staticclass")

def test_instance():
    class A:
        pass
    a = A()
    a.a = a
    gc.collect()
    del a
    expect_nonzero(gc.collect(), "instance")

def test_newinstance():
    class A(object):
        pass
    a = A()
    a.a = a
    gc.collect()
    del a
    expect_nonzero(gc.collect(), "newinstance")
    class B(list):
        pass
    class C(B, A):
        pass
    a = C()
    a.a = a
    gc.collect()
    del a
    expect_nonzero(gc.collect(), "newinstance(2)")

def test_method():
    # Tricky: self.__init__ is a bound method, it references the instance.
    class A:
        def __init__(self):
            self.init = self.__init__
    a = A()
    gc.collect()
    del a
    expect_nonzero(gc.collect(), "method")

def test_finalizer():
    # A() is uncollectable if it is part of a cycle, make sure it shows up
    # in gc.garbage.
    class A:
        def __del__(self): pass
    class B:
        pass
    a = A()
    a.a = a
    id_a = id(a)
    b = B()
    b.b = b
    gc.collect()
    del a
    del b
    expect_nonzero(gc.collect(), "finalizer")
    for obj in gc.garbage:
        if id(obj) == id_a:
            del obj.a
            break
    else:
        raise TestFailed, "didn't find obj in garbage (finalizer)"
    gc.garbage.remove(obj)

def test_function():
    # Tricky: f -> d -> f, code should call d.clear() after the exec to
    # break the cycle.
    d = {}
    exec("def f(): pass\n") in d
    gc.collect()
    del d
    expect(gc.collect(), 2, "function")

def test_frame():
    def f():
        frame = sys._getframe()
    gc.collect()
    f()
    expect(gc.collect(), 1, "frame")


def test_saveall():
    # Verify that cyclic garbage like lists show up in gc.garbage if the
    # SAVEALL option is enabled.
    debug = gc.get_debug()
    gc.set_debug(debug | gc.DEBUG_SAVEALL)
    l = []
    l.append(l)
    id_l = id(l)
    del l
    gc.collect()
    try:
        for obj in gc.garbage:
            if id(obj) == id_l:
                del obj[:]
                break
        else:
            raise TestFailed, "didn't find obj in garbage (saveall)"
        gc.garbage.remove(obj)
    finally:
        gc.set_debug(debug)

def test_del():
    # __del__ methods can trigger collection, make this to happen
    thresholds = gc.get_threshold()
    gc.enable()
    gc.set_threshold(1)

    class A:
        def __del__(self):
            dir(self)
    a = A()
    del a

    gc.disable()
    apply(gc.set_threshold, thresholds)


def test_all():
    gc.collect() # Delete 2nd generation garbage
    run_test("lists", test_list)
    run_test("dicts", test_dict)
    run_test("tuples", test_tuple)
    run_test("classes", test_class)
    run_test("new style classes", test_newstyleclass)
    run_test("instances", test_instance)
    run_test("new instances", test_newinstance)
    run_test("methods", test_method)
    run_test("functions", test_function)
    run_test("frames", test_frame)
    run_test("finalizers", test_finalizer)
    run_test("__del__", test_del)
    run_test("saveall", test_saveall)

def test():
    if verbose:
        print "disabling automatic collection"
    enabled = gc.isenabled()
    gc.disable()
    verify(not gc.isenabled() )
    debug = gc.get_debug()
    gc.set_debug(debug & ~gc.DEBUG_LEAK) # this test is supposed to leak

    try:
        test_all()
    finally:
        gc.set_debug(debug)
        # test gc.enable() even if GC is disabled by default
        if verbose:
            print "restoring automatic collection"
        # make sure to always test gc.enable()
        gc.enable()
        verify(gc.isenabled())
        if not enabled:
            gc.disable()


test()
