# Test enhancements related to descriptors and new-style classes

from test_support import verify, vereq, verbose, TestFailed, TESTFN
from copy import deepcopy

def veris(a, b):
    if a is not b:
        raise TestFailed, "%r is %r" % (a, b)

def testunop(a, res, expr="len(a)", meth="__len__"):
    if verbose: print "checking", expr
    dict = {'a': a}
    vereq(eval(expr, dict), res)
    t = type(a)
    m = getattr(t, meth)
    while meth not in t.__dict__:
        t = t.__bases__[0]
    vereq(m, t.__dict__[meth])
    vereq(m(a), res)
    bm = getattr(a, meth)
    vereq(bm(), res)

def testbinop(a, b, res, expr="a+b", meth="__add__"):
    if verbose: print "checking", expr
    dict = {'a': a, 'b': b}

    # XXX Hack so this passes before 2.3 when -Qnew is specified.
    if meth == "__div__" and 1/2 == 0.5:
        meth = "__truediv__"

    vereq(eval(expr, dict), res)
    t = type(a)
    m = getattr(t, meth)
    while meth not in t.__dict__:
        t = t.__bases__[0]
    vereq(m, t.__dict__[meth])
    vereq(m(a, b), res)
    bm = getattr(a, meth)
    vereq(bm(b), res)

def testternop(a, b, c, res, expr="a[b:c]", meth="__getslice__"):
    if verbose: print "checking", expr
    dict = {'a': a, 'b': b, 'c': c}
    vereq(eval(expr, dict), res)
    t = type(a)
    m = getattr(t, meth)
    while meth not in t.__dict__:
        t = t.__bases__[0]
    vereq(m, t.__dict__[meth])
    vereq(m(a, b, c), res)
    bm = getattr(a, meth)
    vereq(bm(b, c), res)

def testsetop(a, b, res, stmt="a+=b", meth="__iadd__"):
    if verbose: print "checking", stmt
    dict = {'a': deepcopy(a), 'b': b}
    exec stmt in dict
    vereq(dict['a'], res)
    t = type(a)
    m = getattr(t, meth)
    while meth not in t.__dict__:
        t = t.__bases__[0]
    vereq(m, t.__dict__[meth])
    dict['a'] = deepcopy(a)
    m(dict['a'], b)
    vereq(dict['a'], res)
    dict['a'] = deepcopy(a)
    bm = getattr(dict['a'], meth)
    bm(b)
    vereq(dict['a'], res)

def testset2op(a, b, c, res, stmt="a[b]=c", meth="__setitem__"):
    if verbose: print "checking", stmt
    dict = {'a': deepcopy(a), 'b': b, 'c': c}
    exec stmt in dict
    vereq(dict['a'], res)
    t = type(a)
    m = getattr(t, meth)
    while meth not in t.__dict__:
        t = t.__bases__[0]
    vereq(m, t.__dict__[meth])
    dict['a'] = deepcopy(a)
    m(dict['a'], b, c)
    vereq(dict['a'], res)
    dict['a'] = deepcopy(a)
    bm = getattr(dict['a'], meth)
    bm(b, c)
    vereq(dict['a'], res)

def testset3op(a, b, c, d, res, stmt="a[b:c]=d", meth="__setslice__"):
    if verbose: print "checking", stmt
    dict = {'a': deepcopy(a), 'b': b, 'c': c, 'd': d}
    exec stmt in dict
    vereq(dict['a'], res)
    t = type(a)
    while meth not in t.__dict__:
        t = t.__bases__[0]
    m = getattr(t, meth)
    vereq(m, t.__dict__[meth])
    dict['a'] = deepcopy(a)
    m(dict['a'], b, c, d)
    vereq(dict['a'], res)
    dict['a'] = deepcopy(a)
    bm = getattr(dict['a'], meth)
    bm(b, c, d)
    vereq(dict['a'], res)

def class_docstrings():
    class Classic:
        "A classic docstring."
    vereq(Classic.__doc__, "A classic docstring.")
    vereq(Classic.__dict__['__doc__'], "A classic docstring.")

    class Classic2:
        pass
    verify(Classic2.__doc__ is None)

    class NewStatic(object):
        "Another docstring."
    vereq(NewStatic.__doc__, "Another docstring.")
    vereq(NewStatic.__dict__['__doc__'], "Another docstring.")

    class NewStatic2(object):
        pass
    verify(NewStatic2.__doc__ is None)

    class NewDynamic(object):
        "Another docstring."
    vereq(NewDynamic.__doc__, "Another docstring.")
    vereq(NewDynamic.__dict__['__doc__'], "Another docstring.")

    class NewDynamic2(object):
        pass
    verify(NewDynamic2.__doc__ is None)

def lists():
    if verbose: print "Testing list operations..."
    testbinop([1], [2], [1,2], "a+b", "__add__")
    testbinop([1,2,3], 2, 1, "b in a", "__contains__")
    testbinop([1,2,3], 4, 0, "b in a", "__contains__")
    testbinop([1,2,3], 1, 2, "a[b]", "__getitem__")
    testternop([1,2,3], 0, 2, [1,2], "a[b:c]", "__getslice__")
    testsetop([1], [2], [1,2], "a+=b", "__iadd__")
    testsetop([1,2], 3, [1,2,1,2,1,2], "a*=b", "__imul__")
    testunop([1,2,3], 3, "len(a)", "__len__")
    testbinop([1,2], 3, [1,2,1,2,1,2], "a*b", "__mul__")
    testbinop([1,2], 3, [1,2,1,2,1,2], "b*a", "__rmul__")
    testset2op([1,2], 1, 3, [1,3], "a[b]=c", "__setitem__")
    testset3op([1,2,3,4], 1, 3, [5,6], [1,5,6,4], "a[b:c]=d", "__setslice__")

def dicts():
    if verbose: print "Testing dict operations..."
    testbinop({1:2}, {2:1}, -1, "cmp(a,b)", "__cmp__")
    testbinop({1:2,3:4}, 1, 1, "b in a", "__contains__")
    testbinop({1:2,3:4}, 2, 0, "b in a", "__contains__")
    testbinop({1:2,3:4}, 1, 2, "a[b]", "__getitem__")
    d = {1:2,3:4}
    l1 = []
    for i in d.keys(): l1.append(i)
    l = []
    for i in iter(d): l.append(i)
    vereq(l, l1)
    l = []
    for i in d.__iter__(): l.append(i)
    vereq(l, l1)
    l = []
    for i in dict.__iter__(d): l.append(i)
    vereq(l, l1)
    d = {1:2, 3:4}
    testunop(d, 2, "len(a)", "__len__")
    vereq(eval(repr(d), {}), d)
    vereq(eval(d.__repr__(), {}), d)
    testset2op({1:2,3:4}, 2, 3, {1:2,2:3,3:4}, "a[b]=c", "__setitem__")

def dict_constructor():
    if verbose:
        print "Testing dict constructor ..."
    d = dict()
    vereq(d, {})
    d = dict({})
    vereq(d, {})
    d = dict(items={})
    vereq(d, {})
    d = dict({1: 2, 'a': 'b'})
    vereq(d, {1: 2, 'a': 'b'})
    vereq(d, dict(d.items()))
    vereq(d, dict(items=d.iteritems()))
    for badarg in 0, 0L, 0j, "0", [0], (0,):
        try:
            dict(badarg)
        except TypeError:
            pass
        except ValueError:
            if badarg == "0":
                # It's a sequence, and its elements are also sequences (gotta
                # love strings <wink>), but they aren't of length 2, so this
                # one seemed better as a ValueError than a TypeError.
                pass
            else:
                raise TestFailed("no TypeError from dict(%r)" % badarg)
        else:
            raise TestFailed("no TypeError from dict(%r)" % badarg)
    try:
        dict(senseless={})
    except TypeError:
        pass
    else:
        raise TestFailed("no TypeError from dict(senseless={})")

    try:
        dict({}, {})
    except TypeError:
        pass
    else:
        raise TestFailed("no TypeError from dict({}, {})")

    class Mapping:
        # Lacks a .keys() method; will be added later.
        dict = {1:2, 3:4, 'a':1j}

    try:
        dict(Mapping())
    except TypeError:
        pass
    else:
        raise TestFailed("no TypeError from dict(incomplete mapping)")

    Mapping.keys = lambda self: self.dict.keys()
    Mapping.__getitem__ = lambda self, i: self.dict[i]
    d = dict(items=Mapping())
    vereq(d, Mapping.dict)

    # Init from sequence of iterable objects, each producing a 2-sequence.
    class AddressBookEntry:
        def __init__(self, first, last):
            self.first = first
            self.last = last
        def __iter__(self):
            return iter([self.first, self.last])

    d = dict([AddressBookEntry('Tim', 'Warsaw'),
              AddressBookEntry('Barry', 'Peters'),
              AddressBookEntry('Tim', 'Peters'),
              AddressBookEntry('Barry', 'Warsaw')])
    vereq(d, {'Barry': 'Warsaw', 'Tim': 'Peters'})

    d = dict(zip(range(4), range(1, 5)))
    vereq(d, dict([(i, i+1) for i in range(4)]))

    # Bad sequence lengths.
    for bad in [('tooshort',)], [('too', 'long', 'by 1')]:
        try:
            dict(bad)
        except ValueError:
            pass
        else:
            raise TestFailed("no ValueError from dict(%r)" % bad)

def test_dir():
    if verbose:
        print "Testing dir() ..."
    junk = 12
    vereq(dir(), ['junk'])
    del junk

    # Just make sure these don't blow up!
    for arg in 2, 2L, 2j, 2e0, [2], "2", u"2", (2,), {2:2}, type, test_dir:
        dir(arg)

    # Try classic classes.
    class C:
        Cdata = 1
        def Cmethod(self): pass

    cstuff = ['Cdata', 'Cmethod', '__doc__', '__module__']
    vereq(dir(C), cstuff)
    verify('im_self' in dir(C.Cmethod))

    c = C()  # c.__doc__ is an odd thing to see here; ditto c.__module__.
    vereq(dir(c), cstuff)

    c.cdata = 2
    c.cmethod = lambda self: 0
    vereq(dir(c), cstuff + ['cdata', 'cmethod'])
    verify('im_self' in dir(c.Cmethod))

    class A(C):
        Adata = 1
        def Amethod(self): pass

    astuff = ['Adata', 'Amethod'] + cstuff
    vereq(dir(A), astuff)
    verify('im_self' in dir(A.Amethod))
    a = A()
    vereq(dir(a), astuff)
    verify('im_self' in dir(a.Amethod))
    a.adata = 42
    a.amethod = lambda self: 3
    vereq(dir(a), astuff + ['adata', 'amethod'])

    # The same, but with new-style classes.  Since these have object as a
    # base class, a lot more gets sucked in.
    def interesting(strings):
        return [s for s in strings if not s.startswith('_')]

    class C(object):
        Cdata = 1
        def Cmethod(self): pass

    cstuff = ['Cdata', 'Cmethod']
    vereq(interesting(dir(C)), cstuff)

    c = C()
    vereq(interesting(dir(c)), cstuff)
    verify('im_self' in dir(C.Cmethod))

    c.cdata = 2
    c.cmethod = lambda self: 0
    vereq(interesting(dir(c)), cstuff + ['cdata', 'cmethod'])
    verify('im_self' in dir(c.Cmethod))

    class A(C):
        Adata = 1
        def Amethod(self): pass

    astuff = ['Adata', 'Amethod'] + cstuff
    vereq(interesting(dir(A)), astuff)
    verify('im_self' in dir(A.Amethod))
    a = A()
    vereq(interesting(dir(a)), astuff)
    a.adata = 42
    a.amethod = lambda self: 3
    vereq(interesting(dir(a)), astuff + ['adata', 'amethod'])
    verify('im_self' in dir(a.Amethod))

    # Try a module subclass.
    import sys
    class M(type(sys)):
        pass
    minstance = M()
    minstance.b = 2
    minstance.a = 1
    vereq(dir(minstance), ['a', 'b'])

    class M2(M):
        def getdict(self):
            return "Not a dict!"
        __dict__ = property(getdict)

    m2instance = M2()
    m2instance.b = 2
    m2instance.a = 1
    vereq(m2instance.__dict__, "Not a dict!")
    try:
        dir(m2instance)
    except TypeError:
        pass

    # Two essentially featureless objects, just inheriting stuff from
    # object.
    vereq(dir(None), dir(Ellipsis))

binops = {
    'add': '+',
    'sub': '-',
    'mul': '*',
    'div': '/',
    'mod': '%',
    'divmod': 'divmod',
    'pow': '**',
    'lshift': '<<',
    'rshift': '>>',
    'and': '&',
    'xor': '^',
    'or': '|',
    'cmp': 'cmp',
    'lt': '<',
    'le': '<=',
    'eq': '==',
    'ne': '!=',
    'gt': '>',
    'ge': '>=',
    }

for name, expr in binops.items():
    if expr.islower():
        expr = expr + "(a, b)"
    else:
        expr = 'a %s b' % expr
    binops[name] = expr

unops = {
    'pos': '+',
    'neg': '-',
    'abs': 'abs',
    'invert': '~',
    'int': 'int',
    'long': 'long',
    'float': 'float',
    'oct': 'oct',
    'hex': 'hex',
    }

for name, expr in unops.items():
    if expr.islower():
        expr = expr + "(a)"
    else:
        expr = '%s a' % expr
    unops[name] = expr

def numops(a, b, skip=[]):
    dict = {'a': a, 'b': b}
    for name, expr in binops.items():
        if name not in skip:
            name = "__%s__" % name
            if hasattr(a, name):
                res = eval(expr, dict)
                testbinop(a, b, res, expr, name)
    for name, expr in unops.items():
        if name not in skip:
            name = "__%s__" % name
            if hasattr(a, name):
                res = eval(expr, dict)
                testunop(a, res, expr, name)

def ints():
    if verbose: print "Testing int operations..."
    numops(100, 3)

def longs():
    if verbose: print "Testing long operations..."
    numops(100L, 3L)

def floats():
    if verbose: print "Testing float operations..."
    numops(100.0, 3.0)

def complexes():
    if verbose: print "Testing complex operations..."
    numops(100.0j, 3.0j, skip=['lt', 'le', 'gt', 'ge', 'int', 'long', 'float'])
    class Number(complex):
        __slots__ = ['prec']
        def __new__(cls, *args, **kwds):
            result = complex.__new__(cls, *args)
            result.prec = kwds.get('prec', 12)
            return result
        def __repr__(self):
            prec = self.prec
            if self.imag == 0.0:
                return "%.*g" % (prec, self.real)
            if self.real == 0.0:
                return "%.*gj" % (prec, self.imag)
            return "(%.*g+%.*gj)" % (prec, self.real, prec, self.imag)
        __str__ = __repr__

    a = Number(3.14, prec=6)
    vereq(`a`, "3.14")
    vereq(a.prec, 6)

    a = Number(a, prec=2)
    vereq(`a`, "3.1")
    vereq(a.prec, 2)

    a = Number(234.5)
    vereq(`a`, "234.5")
    vereq(a.prec, 12)

def spamlists():
    if verbose: print "Testing spamlist operations..."
    import copy, xxsubtype as spam
    def spamlist(l, memo=None):
        import xxsubtype as spam
        return spam.spamlist(l)
    # This is an ugly hack:
    copy._deepcopy_dispatch[spam.spamlist] = spamlist

    testbinop(spamlist([1]), spamlist([2]), spamlist([1,2]), "a+b", "__add__")
    testbinop(spamlist([1,2,3]), 2, 1, "b in a", "__contains__")
    testbinop(spamlist([1,2,3]), 4, 0, "b in a", "__contains__")
    testbinop(spamlist([1,2,3]), 1, 2, "a[b]", "__getitem__")
    testternop(spamlist([1,2,3]), 0, 2, spamlist([1,2]),
               "a[b:c]", "__getslice__")
    testsetop(spamlist([1]), spamlist([2]), spamlist([1,2]),
              "a+=b", "__iadd__")
    testsetop(spamlist([1,2]), 3, spamlist([1,2,1,2,1,2]), "a*=b", "__imul__")
    testunop(spamlist([1,2,3]), 3, "len(a)", "__len__")
    testbinop(spamlist([1,2]), 3, spamlist([1,2,1,2,1,2]), "a*b", "__mul__")
    testbinop(spamlist([1,2]), 3, spamlist([1,2,1,2,1,2]), "b*a", "__rmul__")
    testset2op(spamlist([1,2]), 1, 3, spamlist([1,3]), "a[b]=c", "__setitem__")
    testset3op(spamlist([1,2,3,4]), 1, 3, spamlist([5,6]),
               spamlist([1,5,6,4]), "a[b:c]=d", "__setslice__")
    # Test subclassing
    class C(spam.spamlist):
        def foo(self): return 1
    a = C()
    vereq(a, [])
    vereq(a.foo(), 1)
    a.append(100)
    vereq(a, [100])
    vereq(a.getstate(), 0)
    a.setstate(42)
    vereq(a.getstate(), 42)

def spamdicts():
    if verbose: print "Testing spamdict operations..."
    import copy, xxsubtype as spam
    def spamdict(d, memo=None):
        import xxsubtype as spam
        sd = spam.spamdict()
        for k, v in d.items(): sd[k] = v
        return sd
    # This is an ugly hack:
    copy._deepcopy_dispatch[spam.spamdict] = spamdict

    testbinop(spamdict({1:2}), spamdict({2:1}), -1, "cmp(a,b)", "__cmp__")
    testbinop(spamdict({1:2,3:4}), 1, 1, "b in a", "__contains__")
    testbinop(spamdict({1:2,3:4}), 2, 0, "b in a", "__contains__")
    testbinop(spamdict({1:2,3:4}), 1, 2, "a[b]", "__getitem__")
    d = spamdict({1:2,3:4})
    l1 = []
    for i in d.keys(): l1.append(i)
    l = []
    for i in iter(d): l.append(i)
    vereq(l, l1)
    l = []
    for i in d.__iter__(): l.append(i)
    vereq(l, l1)
    l = []
    for i in type(spamdict({})).__iter__(d): l.append(i)
    vereq(l, l1)
    straightd = {1:2, 3:4}
    spamd = spamdict(straightd)
    testunop(spamd, 2, "len(a)", "__len__")
    testunop(spamd, repr(straightd), "repr(a)", "__repr__")
    testset2op(spamdict({1:2,3:4}), 2, 3, spamdict({1:2,2:3,3:4}),
               "a[b]=c", "__setitem__")
    # Test subclassing
    class C(spam.spamdict):
        def foo(self): return 1
    a = C()
    vereq(a.items(), [])
    vereq(a.foo(), 1)
    a['foo'] = 'bar'
    vereq(a.items(), [('foo', 'bar')])
    vereq(a.getstate(), 0)
    a.setstate(100)
    vereq(a.getstate(), 100)

def pydicts():
    if verbose: print "Testing Python subclass of dict..."
    verify(issubclass(dict, dict))
    verify(isinstance({}, dict))
    d = dict()
    vereq(d, {})
    verify(d.__class__ is dict)
    verify(isinstance(d, dict))
    class C(dict):
        state = -1
        def __init__(self, *a, **kw):
            if a:
                vereq(len(a), 1)
                self.state = a[0]
            if kw:
                for k, v in kw.items(): self[v] = k
        def __getitem__(self, key):
            return self.get(key, 0)
        def __setitem__(self, key, value):
            verify(isinstance(key, type(0)))
            dict.__setitem__(self, key, value)
        def setstate(self, state):
            self.state = state
        def getstate(self):
            return self.state
    verify(issubclass(C, dict))
    a1 = C(12)
    vereq(a1.state, 12)
    a2 = C(foo=1, bar=2)
    vereq(a2[1] == 'foo' and a2[2], 'bar')
    a = C()
    vereq(a.state, -1)
    vereq(a.getstate(), -1)
    a.setstate(0)
    vereq(a.state, 0)
    vereq(a.getstate(), 0)
    a.setstate(10)
    vereq(a.state, 10)
    vereq(a.getstate(), 10)
    vereq(a[42], 0)
    a[42] = 24
    vereq(a[42], 24)
    if verbose: print "pydict stress test ..."
    N = 50
    for i in range(N):
        a[i] = C()
        for j in range(N):
            a[i][j] = i*j
    for i in range(N):
        for j in range(N):
            vereq(a[i][j], i*j)

def pylists():
    if verbose: print "Testing Python subclass of list..."
    class C(list):
        def __getitem__(self, i):
            return list.__getitem__(self, i) + 100
        def __getslice__(self, i, j):
            return (i, j)
    a = C()
    a.extend([0,1,2])
    vereq(a[0], 100)
    vereq(a[1], 101)
    vereq(a[2], 102)
    vereq(a[100:200], (100,200))

def metaclass():
    if verbose: print "Testing __metaclass__..."
    class C:
        __metaclass__ = type
        def __init__(self):
            self.__state = 0
        def getstate(self):
            return self.__state
        def setstate(self, state):
            self.__state = state
    a = C()
    vereq(a.getstate(), 0)
    a.setstate(10)
    vereq(a.getstate(), 10)
    class D:
        class __metaclass__(type):
            def myself(cls): return cls
    vereq(D.myself(), D)
    d = D()
    verify(d.__class__ is D)
    class M1(type):
        def __new__(cls, name, bases, dict):
            dict['__spam__'] = 1
            return type.__new__(cls, name, bases, dict)
    class C:
        __metaclass__ = M1
    vereq(C.__spam__, 1)
    c = C()
    vereq(c.__spam__, 1)

    class _instance(object):
        pass
    class M2(object):
        def __new__(cls, name, bases, dict):
            self = object.__new__(cls)
            self.name = name
            self.bases = bases
            self.dict = dict
            return self
        __new__ = staticmethod(__new__)
        def __call__(self):
            it = _instance()
            # Early binding of methods
            for key in self.dict:
                if key.startswith("__"):
                    continue
                setattr(it, key, self.dict[key].__get__(it, self))
            return it
    class C:
        __metaclass__ = M2
        def spam(self):
            return 42
    vereq(C.name, 'C')
    vereq(C.bases, ())
    verify('spam' in C.dict)
    c = C()
    vereq(c.spam(), 42)

    # More metaclass examples

    class autosuper(type):
        # Automatically add __super to the class
        # This trick only works for dynamic classes
        def __new__(metaclass, name, bases, dict):
            cls = super(autosuper, metaclass).__new__(metaclass,
                                                      name, bases, dict)
            # Name mangling for __super removes leading underscores
            while name[:1] == "_":
                name = name[1:]
            if name:
                name = "_%s__super" % name
            else:
                name = "__super"
            setattr(cls, name, super(cls))
            return cls
    class A:
        __metaclass__ = autosuper
        def meth(self):
            return "A"
    class B(A):
        def meth(self):
            return "B" + self.__super.meth()
    class C(A):
        def meth(self):
            return "C" + self.__super.meth()
    class D(C, B):
        def meth(self):
            return "D" + self.__super.meth()
    vereq(D().meth(), "DCBA")
    class E(B, C):
        def meth(self):
            return "E" + self.__super.meth()
    vereq(E().meth(), "EBCA")

    class autoproperty(type):
        # Automatically create property attributes when methods
        # named _get_x and/or _set_x are found
        def __new__(metaclass, name, bases, dict):
            hits = {}
            for key, val in dict.iteritems():
                if key.startswith("_get_"):
                    key = key[5:]
                    get, set = hits.get(key, (None, None))
                    get = val
                    hits[key] = get, set
                elif key.startswith("_set_"):
                    key = key[5:]
                    get, set = hits.get(key, (None, None))
                    set = val
                    hits[key] = get, set
            for key, (get, set) in hits.iteritems():
                dict[key] = property(get, set)
            return super(autoproperty, metaclass).__new__(metaclass,
                                                        name, bases, dict)
    class A:
        __metaclass__ = autoproperty
        def _get_x(self):
            return -self.__x
        def _set_x(self, x):
            self.__x = -x
    a = A()
    verify(not hasattr(a, "x"))
    a.x = 12
    vereq(a.x, 12)
    vereq(a._A__x, -12)

    class multimetaclass(autoproperty, autosuper):
        # Merge of multiple cooperating metaclasses
        pass
    class A:
        __metaclass__ = multimetaclass
        def _get_x(self):
            return "A"
    class B(A):
        def _get_x(self):
            return "B" + self.__super._get_x()
    class C(A):
        def _get_x(self):
            return "C" + self.__super._get_x()
    class D(C, B):
        def _get_x(self):
            return "D" + self.__super._get_x()
    vereq(D().x, "DCBA")

    # Make sure type(x) doesn't call x.__class__.__init__
    class T(type):
        counter = 0
        def __init__(self, *args):
            T.counter += 1
    class C:
        __metaclass__ = T
    vereq(T.counter, 1)
    a = C()
    vereq(type(a), C)
    vereq(T.counter, 1)

    class C(object): pass
    c = C()
    try: c()
    except TypeError: pass
    else: raise TestError, "calling object w/o call method should raise TypeError"

def pymods():
    if verbose: print "Testing Python subclass of module..."
    log = []
    import sys
    MT = type(sys)
    class MM(MT):
        def __init__(self):
            MT.__init__(self)
        def __getattribute__(self, name):
            log.append(("getattr", name))
            return MT.__getattribute__(self, name)
        def __setattr__(self, name, value):
            log.append(("setattr", name, value))
            MT.__setattr__(self, name, value)
        def __delattr__(self, name):
            log.append(("delattr", name))
            MT.__delattr__(self, name)
    a = MM()
    a.foo = 12
    x = a.foo
    del a.foo
    vereq(log, [("setattr", "foo", 12),
                ("getattr", "foo"),
                ("delattr", "foo")])

def multi():
    if verbose: print "Testing multiple inheritance..."
    class C(object):
        def __init__(self):
            self.__state = 0
        def getstate(self):
            return self.__state
        def setstate(self, state):
            self.__state = state
    a = C()
    vereq(a.getstate(), 0)
    a.setstate(10)
    vereq(a.getstate(), 10)
    class D(dict, C):
        def __init__(self):
            type({}).__init__(self)
            C.__init__(self)
    d = D()
    vereq(d.keys(), [])
    d["hello"] = "world"
    vereq(d.items(), [("hello", "world")])
    vereq(d["hello"], "world")
    vereq(d.getstate(), 0)
    d.setstate(10)
    vereq(d.getstate(), 10)
    vereq(D.__mro__, (D, dict, C, object))

    # SF bug #442833
    class Node(object):
        def __int__(self):
            return int(self.foo())
        def foo(self):
            return "23"
    class Frag(Node, list):
        def foo(self):
            return "42"
    vereq(Node().__int__(), 23)
    vereq(int(Node()), 23)
    vereq(Frag().__int__(), 42)
    vereq(int(Frag()), 42)

    # MI mixing classic and new-style classes.

    class A:
        x = 1

    class B(A):
        pass

    class C(A):
        x = 2

    class D(B, C):
        pass
    vereq(D.x, 1)

    # Classic MRO is preserved for a classic base class.
    class E(D, object):
        pass
    vereq(E.__mro__, (E, D, B, A, C, object))
    vereq(E.x, 1)

    # But with a mix of classic bases, their MROs are combined using
    # new-style MRO.
    class F(B, C, object):
        pass
    vereq(F.__mro__, (F, B, C, A, object))
    vereq(F.x, 2)

    # Try something else.
    class C:
        def cmethod(self):
            return "C a"
        def all_method(self):
            return "C b"

    class M1(C, object):
        def m1method(self):
            return "M1 a"
        def all_method(self):
            return "M1 b"

    vereq(M1.__mro__, (M1, C, object))
    m = M1()
    vereq(m.cmethod(), "C a")
    vereq(m.m1method(), "M1 a")
    vereq(m.all_method(), "M1 b")

    class D(C):
        def dmethod(self):
            return "D a"
        def all_method(self):
            return "D b"

    class M2(object, D):
        def m2method(self):
            return "M2 a"
        def all_method(self):
            return "M2 b"

    vereq(M2.__mro__, (M2, object, D, C))
    m = M2()
    vereq(m.cmethod(), "C a")
    vereq(m.dmethod(), "D a")
    vereq(m.m2method(), "M2 a")
    vereq(m.all_method(), "M2 b")

    class M3(M1, object, M2):
        def m3method(self):
            return "M3 a"
        def all_method(self):
            return "M3 b"
    # XXX Expected this (the commented-out result):
    # vereq(M3.__mro__, (M3, M1, M2, object, D, C))
    vereq(M3.__mro__, (M3, M1, M2, D, C, object))  # XXX ?
    m = M3()
    vereq(m.cmethod(), "C a")
    vereq(m.dmethod(), "D a")
    vereq(m.m1method(), "M1 a")
    vereq(m.m2method(), "M2 a")
    vereq(m.m3method(), "M3 a")
    vereq(m.all_method(), "M3 b")

    class Classic:
        pass
    try:
        class New(Classic):
            __metaclass__ = type
    except TypeError:
        pass
    else:
        raise TestFailed, "new class with only classic bases - shouldn't be"

def diamond():
    if verbose: print "Testing multiple inheritance special cases..."
    class A(object):
        def spam(self): return "A"
    vereq(A().spam(), "A")
    class B(A):
        def boo(self): return "B"
        def spam(self): return "B"
    vereq(B().spam(), "B")
    vereq(B().boo(), "B")
    class C(A):
        def boo(self): return "C"
    vereq(C().spam(), "A")
    vereq(C().boo(), "C")
    class D(B, C): pass
    vereq(D().spam(), "B")
    vereq(D().boo(), "B")
    vereq(D.__mro__, (D, B, C, A, object))
    class E(C, B): pass
    vereq(E().spam(), "B")
    vereq(E().boo(), "C")
    vereq(E.__mro__, (E, C, B, A, object))
    class F(D, E): pass
    vereq(F().spam(), "B")
    vereq(F().boo(), "B")
    vereq(F.__mro__, (F, D, E, B, C, A, object))
    class G(E, D): pass
    vereq(G().spam(), "B")
    vereq(G().boo(), "C")
    vereq(G.__mro__, (G, E, D, C, B, A, object))

def objects():
    if verbose: print "Testing object class..."
    a = object()
    vereq(a.__class__, object)
    vereq(type(a), object)
    b = object()
    verify(a is not b)
    verify(not hasattr(a, "foo"))
    try:
        a.foo = 12
    except (AttributeError, TypeError):
        pass
    else:
        verify(0, "object() should not allow setting a foo attribute")
    verify(not hasattr(object(), "__dict__"))

    class Cdict(object):
        pass
    x = Cdict()
    vereq(x.__dict__, {})
    x.foo = 1
    vereq(x.foo, 1)
    vereq(x.__dict__, {'foo': 1})

def slots():
    if verbose: print "Testing __slots__..."
    class C0(object):
        __slots__ = []
    x = C0()
    verify(not hasattr(x, "__dict__"))
    verify(not hasattr(x, "foo"))

    class C1(object):
        __slots__ = ['a']
    x = C1()
    verify(not hasattr(x, "__dict__"))
    verify(not hasattr(x, "a"))
    x.a = 1
    vereq(x.a, 1)
    x.a = None
    veris(x.a, None)
    del x.a
    verify(not hasattr(x, "a"))

    class C3(object):
        __slots__ = ['a', 'b', 'c']
    x = C3()
    verify(not hasattr(x, "__dict__"))
    verify(not hasattr(x, 'a'))
    verify(not hasattr(x, 'b'))
    verify(not hasattr(x, 'c'))
    x.a = 1
    x.b = 2
    x.c = 3
    vereq(x.a, 1)
    vereq(x.b, 2)
    vereq(x.c, 3)

    # Test leaks
    class Counted(object):
        counter = 0    # counts the number of instances alive
        def __init__(self):
            Counted.counter += 1
        def __del__(self):
            Counted.counter -= 1
    class C(object):
        __slots__ = ['a', 'b', 'c']
    x = C()
    x.a = Counted()
    x.b = Counted()
    x.c = Counted()
    vereq(Counted.counter, 3)
    del x
    vereq(Counted.counter, 0)
    class D(C):
        pass
    x = D()
    x.a = Counted()
    x.z = Counted()
    vereq(Counted.counter, 2)
    del x
    vereq(Counted.counter, 0)
    class E(D):
        __slots__ = ['e']
    x = E()
    x.a = Counted()
    x.z = Counted()
    x.e = Counted()
    vereq(Counted.counter, 3)
    del x
    vereq(Counted.counter, 0)

def dynamics():
    if verbose: print "Testing class attribute propagation..."
    class D(object):
        pass
    class E(D):
        pass
    class F(D):
        pass
    D.foo = 1
    vereq(D.foo, 1)
    # Test that dynamic attributes are inherited
    vereq(E.foo, 1)
    vereq(F.foo, 1)
    # Test dynamic instances
    class C(object):
        pass
    a = C()
    verify(not hasattr(a, "foobar"))
    C.foobar = 2
    vereq(a.foobar, 2)
    C.method = lambda self: 42
    vereq(a.method(), 42)
    C.__repr__ = lambda self: "C()"
    vereq(repr(a), "C()")
    C.__int__ = lambda self: 100
    vereq(int(a), 100)
    vereq(a.foobar, 2)
    verify(not hasattr(a, "spam"))
    def mygetattr(self, name):
        if name == "spam":
            return "spam"
        raise AttributeError
    C.__getattr__ = mygetattr
    vereq(a.spam, "spam")
    a.new = 12
    vereq(a.new, 12)
    def mysetattr(self, name, value):
        if name == "spam":
            raise AttributeError
        return object.__setattr__(self, name, value)
    C.__setattr__ = mysetattr
    try:
        a.spam = "not spam"
    except AttributeError:
        pass
    else:
        verify(0, "expected AttributeError")
    vereq(a.spam, "spam")
    class D(C):
        pass
    d = D()
    d.foo = 1
    vereq(d.foo, 1)

    # Test handling of int*seq and seq*int
    class I(int):
        pass
    vereq("a"*I(2), "aa")
    vereq(I(2)*"a", "aa")
    vereq(2*I(3), 6)
    vereq(I(3)*2, 6)
    vereq(I(3)*I(2), 6)

    # Test handling of long*seq and seq*long
    class L(long):
        pass
    vereq("a"*L(2L), "aa")
    vereq(L(2L)*"a", "aa")
    vereq(2*L(3), 6)
    vereq(L(3)*2, 6)
    vereq(L(3)*L(2), 6)

    # Test comparison of classes with dynamic metaclasses
    class dynamicmetaclass(type):
        pass
    class someclass:
        __metaclass__ = dynamicmetaclass
    verify(someclass != object)

def errors():
    if verbose: print "Testing errors..."

    try:
        class C(list, dict):
            pass
    except TypeError:
        pass
    else:
        verify(0, "inheritance from both list and dict should be illegal")

    try:
        class C(object, None):
            pass
    except TypeError:
        pass
    else:
        verify(0, "inheritance from non-type should be illegal")
    class Classic:
        pass

    try:
        class C(type(len)):
            pass
    except TypeError:
        pass
    else:
        verify(0, "inheritance from CFunction should be illegal")

    try:
        class C(object):
            __slots__ = 1
    except TypeError:
        pass
    else:
        verify(0, "__slots__ = 1 should be illegal")

    try:
        class C(object):
            __slots__ = [1]
    except TypeError:
        pass
    else:
        verify(0, "__slots__ = [1] should be illegal")

def classmethods():
    if verbose: print "Testing class methods..."
    class C(object):
        def foo(*a): return a
        goo = classmethod(foo)
    c = C()
    vereq(C.goo(1), (C, 1))
    vereq(c.goo(1), (C, 1))
    vereq(c.foo(1), (c, 1))
    class D(C):
        pass
    d = D()
    vereq(D.goo(1), (D, 1))
    vereq(d.goo(1), (D, 1))
    vereq(d.foo(1), (d, 1))
    vereq(D.foo(d, 1), (d, 1))

def staticmethods():
    if verbose: print "Testing static methods..."
    class C(object):
        def foo(*a): return a
        goo = staticmethod(foo)
    c = C()
    vereq(C.goo(1), (1,))
    vereq(c.goo(1), (1,))
    vereq(c.foo(1), (c, 1,))
    class D(C):
        pass
    d = D()
    vereq(D.goo(1), (1,))
    vereq(d.goo(1), (1,))
    vereq(d.foo(1), (d, 1))
    vereq(D.foo(d, 1), (d, 1))

def classic():
    if verbose: print "Testing classic classes..."
    class C:
        def foo(*a): return a
        goo = classmethod(foo)
    c = C()
    vereq(C.goo(1), (C, 1))
    vereq(c.goo(1), (C, 1))
    vereq(c.foo(1), (c, 1))
    class D(C):
        pass
    d = D()
    vereq(D.goo(1), (D, 1))
    vereq(d.goo(1), (D, 1))
    vereq(d.foo(1), (d, 1))
    vereq(D.foo(d, 1), (d, 1))
    class E: # *not* subclassing from C
        foo = C.foo
    vereq(E().foo, C.foo) # i.e., unbound
    verify(repr(C.foo.__get__(C())).startswith("<bound method "))

def compattr():
    if verbose: print "Testing computed attributes..."
    class C(object):
        class computed_attribute(object):
            def __init__(self, get, set=None):
                self.__get = get
                self.__set = set
            def __get__(self, obj, type=None):
                return self.__get(obj)
            def __set__(self, obj, value):
                return self.__set(obj, value)
        def __init__(self):
            self.__x = 0
        def __get_x(self):
            x = self.__x
            self.__x = x+1
            return x
        def __set_x(self, x):
            self.__x = x
        x = computed_attribute(__get_x, __set_x)
    a = C()
    vereq(a.x, 0)
    vereq(a.x, 1)
    a.x = 10
    vereq(a.x, 10)
    vereq(a.x, 11)

def newslot():
    if verbose: print "Testing __new__ slot override..."
    class C(list):
        def __new__(cls):
            self = list.__new__(cls)
            self.foo = 1
            return self
        def __init__(self):
            self.foo = self.foo + 2
    a = C()
    vereq(a.foo, 3)
    verify(a.__class__ is C)
    class D(C):
        pass
    b = D()
    vereq(b.foo, 3)
    verify(b.__class__ is D)

def altmro():
    if verbose: print "Testing mro() and overriding it..."
    class A(object):
        def f(self): return "A"
    class B(A):
        pass
    class C(A):
        def f(self): return "C"
    class D(B, C):
        pass
    vereq(D.mro(), [D, B, C, A, object])
    vereq(D.__mro__, (D, B, C, A, object))
    vereq(D().f(), "C")
    class PerverseMetaType(type):
        def mro(cls):
            L = type.mro(cls)
            L.reverse()
            return L
    class X(A,B,C,D):
        __metaclass__ = PerverseMetaType
    vereq(X.__mro__, (object, A, C, B, D, X))
    vereq(X().f(), "A")

def overloading():
    if verbose: print "Testing operator overloading..."

    class B(object):
        "Intermediate class because object doesn't have a __setattr__"

    class C(B):

        def __getattr__(self, name):
            if name == "foo":
                return ("getattr", name)
            else:
                raise AttributeError
        def __setattr__(self, name, value):
            if name == "foo":
                self.setattr = (name, value)
            else:
                return B.__setattr__(self, name, value)
        def __delattr__(self, name):
            if name == "foo":
                self.delattr = name
            else:
                return B.__delattr__(self, name)

        def __getitem__(self, key):
            return ("getitem", key)
        def __setitem__(self, key, value):
            self.setitem = (key, value)
        def __delitem__(self, key):
            self.delitem = key

        def __getslice__(self, i, j):
            return ("getslice", i, j)
        def __setslice__(self, i, j, value):
            self.setslice = (i, j, value)
        def __delslice__(self, i, j):
            self.delslice = (i, j)

    a = C()
    vereq(a.foo, ("getattr", "foo"))
    a.foo = 12
    vereq(a.setattr, ("foo", 12))
    del a.foo
    vereq(a.delattr, "foo")

    vereq(a[12], ("getitem", 12))
    a[12] = 21
    vereq(a.setitem, (12, 21))
    del a[12]
    vereq(a.delitem, 12)

    vereq(a[0:10], ("getslice", 0, 10))
    a[0:10] = "foo"
    vereq(a.setslice, (0, 10, "foo"))
    del a[0:10]
    vereq(a.delslice, (0, 10))

def methods():
    if verbose: print "Testing methods..."
    class C(object):
        def __init__(self, x):
            self.x = x
        def foo(self):
            return self.x
    c1 = C(1)
    vereq(c1.foo(), 1)
    class D(C):
        boo = C.foo
        goo = c1.foo
    d2 = D(2)
    vereq(d2.foo(), 2)
    vereq(d2.boo(), 2)
    vereq(d2.goo(), 1)
    class E(object):
        foo = C.foo
    vereq(E().foo, C.foo) # i.e., unbound
    verify(repr(C.foo.__get__(C(1))).startswith("<bound method "))

def specials():
    # Test operators like __hash__ for which a built-in default exists
    if verbose: print "Testing special operators..."
    # Test the default behavior for static classes
    class C(object):
        def __getitem__(self, i):
            if 0 <= i < 10: return i
            raise IndexError
    c1 = C()
    c2 = C()
    verify(not not c1)
    vereq(hash(c1), id(c1))
    vereq(cmp(c1, c2), cmp(id(c1), id(c2)))
    vereq(c1, c1)
    verify(c1 != c2)
    verify(not c1 != c1)
    verify(not c1 == c2)
    # Note that the module name appears in str/repr, and that varies
    # depending on whether this test is run standalone or from a framework.
    verify(str(c1).find('C object at ') >= 0)
    vereq(str(c1), repr(c1))
    verify(-1 not in c1)
    for i in range(10):
        verify(i in c1)
    verify(10 not in c1)
    # Test the default behavior for dynamic classes
    class D(object):
        def __getitem__(self, i):
            if 0 <= i < 10: return i
            raise IndexError
    d1 = D()
    d2 = D()
    verify(not not d1)
    vereq(hash(d1), id(d1))
    vereq(cmp(d1, d2), cmp(id(d1), id(d2)))
    vereq(d1, d1)
    verify(d1 != d2)
    verify(not d1 != d1)
    verify(not d1 == d2)
    # Note that the module name appears in str/repr, and that varies
    # depending on whether this test is run standalone or from a framework.
    verify(str(d1).find('D object at ') >= 0)
    vereq(str(d1), repr(d1))
    verify(-1 not in d1)
    for i in range(10):
        verify(i in d1)
    verify(10 not in d1)
    # Test overridden behavior for static classes
    class Proxy(object):
        def __init__(self, x):
            self.x = x
        def __nonzero__(self):
            return not not self.x
        def __hash__(self):
            return hash(self.x)
        def __eq__(self, other):
            return self.x == other
        def __ne__(self, other):
            return self.x != other
        def __cmp__(self, other):
            return cmp(self.x, other.x)
        def __str__(self):
            return "Proxy:%s" % self.x
        def __repr__(self):
            return "Proxy(%r)" % self.x
        def __contains__(self, value):
            return value in self.x
    p0 = Proxy(0)
    p1 = Proxy(1)
    p_1 = Proxy(-1)
    verify(not p0)
    verify(not not p1)
    vereq(hash(p0), hash(0))
    vereq(p0, p0)
    verify(p0 != p1)
    verify(not p0 != p0)
    vereq(not p0, p1)
    vereq(cmp(p0, p1), -1)
    vereq(cmp(p0, p0), 0)
    vereq(cmp(p0, p_1), 1)
    vereq(str(p0), "Proxy:0")
    vereq(repr(p0), "Proxy(0)")
    p10 = Proxy(range(10))
    verify(-1 not in p10)
    for i in range(10):
        verify(i in p10)
    verify(10 not in p10)
    # Test overridden behavior for dynamic classes
    class DProxy(object):
        def __init__(self, x):
            self.x = x
        def __nonzero__(self):
            return not not self.x
        def __hash__(self):
            return hash(self.x)
        def __eq__(self, other):
            return self.x == other
        def __ne__(self, other):
            return self.x != other
        def __cmp__(self, other):
            return cmp(self.x, other.x)
        def __str__(self):
            return "DProxy:%s" % self.x
        def __repr__(self):
            return "DProxy(%r)" % self.x
        def __contains__(self, value):
            return value in self.x
    p0 = DProxy(0)
    p1 = DProxy(1)
    p_1 = DProxy(-1)
    verify(not p0)
    verify(not not p1)
    vereq(hash(p0), hash(0))
    vereq(p0, p0)
    verify(p0 != p1)
    verify(not p0 != p0)
    vereq(not p0, p1)
    vereq(cmp(p0, p1), -1)
    vereq(cmp(p0, p0), 0)
    vereq(cmp(p0, p_1), 1)
    vereq(str(p0), "DProxy:0")
    vereq(repr(p0), "DProxy(0)")
    p10 = DProxy(range(10))
    verify(-1 not in p10)
    for i in range(10):
        verify(i in p10)
    verify(10 not in p10)
    # Safety test for __cmp__
    def unsafecmp(a, b):
        try:
            a.__class__.__cmp__(a, b)
        except TypeError:
            pass
        else:
            raise TestFailed, "shouldn't allow %s.__cmp__(%r, %r)" % (
                a.__class__, a, b)
    unsafecmp(u"123", "123")
    unsafecmp("123", u"123")
    unsafecmp(1, 1.0)
    unsafecmp(1.0, 1)
    unsafecmp(1, 1L)
    unsafecmp(1L, 1)

def weakrefs():
    if verbose: print "Testing weak references..."
    import weakref
    class C(object):
        pass
    c = C()
    r = weakref.ref(c)
    verify(r() is c)
    del c
    verify(r() is None)
    del r
    class NoWeak(object):
        __slots__ = ['foo']
    no = NoWeak()
    try:
        weakref.ref(no)
    except TypeError, msg:
        verify(str(msg).find("weak reference") >= 0)
    else:
        verify(0, "weakref.ref(no) should be illegal")
    class Weak(object):
        __slots__ = ['foo', '__weakref__']
    yes = Weak()
    r = weakref.ref(yes)
    verify(r() is yes)
    del yes
    verify(r() is None)
    del r

def properties():
    if verbose: print "Testing property..."
    class C(object):
        def getx(self):
            return self.__x
        def setx(self, value):
            self.__x = value
        def delx(self):
            del self.__x
        x = property(getx, setx, delx, doc="I'm the x property.")
    a = C()
    verify(not hasattr(a, "x"))
    a.x = 42
    vereq(a._C__x, 42)
    vereq(a.x, 42)
    del a.x
    verify(not hasattr(a, "x"))
    verify(not hasattr(a, "_C__x"))
    C.x.__set__(a, 100)
    vereq(C.x.__get__(a), 100)
##    C.x.__set__(a)
##    verify(not hasattr(a, "x"))

    raw = C.__dict__['x']
    verify(isinstance(raw, property))

    attrs = dir(raw)
    verify("__doc__" in attrs)
    verify("fget" in attrs)
    verify("fset" in attrs)
    verify("fdel" in attrs)

    vereq(raw.__doc__, "I'm the x property.")
    verify(raw.fget is C.__dict__['getx'])
    verify(raw.fset is C.__dict__['setx'])
    verify(raw.fdel is C.__dict__['delx'])

    for attr in "__doc__", "fget", "fset", "fdel":
        try:
            setattr(raw, attr, 42)
        except TypeError, msg:
            if str(msg).find('readonly') < 0:
                raise TestFailed("when setting readonly attr %r on a "
                                 "property, got unexpected TypeError "
                                 "msg %r" % (attr, str(msg)))
        else:
            raise TestFailed("expected TypeError from trying to set "
                             "readonly %r attr on a property" % attr)

def supers():
    if verbose: print "Testing super..."

    class A(object):
        def meth(self, a):
            return "A(%r)" % a

    vereq(A().meth(1), "A(1)")

    class B(A):
        def __init__(self):
            self.__super = super(B, self)
        def meth(self, a):
            return "B(%r)" % a + self.__super.meth(a)

    vereq(B().meth(2), "B(2)A(2)")

    class C(A):
        def meth(self, a):
            return "C(%r)" % a + self.__super.meth(a)
    C._C__super = super(C)

    vereq(C().meth(3), "C(3)A(3)")

    class D(C, B):
        def meth(self, a):
            return "D(%r)" % a + super(D, self).meth(a)

    vereq(D().meth(4), "D(4)C(4)B(4)A(4)")

    # Test for subclassing super

    class mysuper(super):
        def __init__(self, *args):
            return super(mysuper, self).__init__(*args)

    class E(D):
        def meth(self, a):
            return "E(%r)" % a + mysuper(E, self).meth(a)

    vereq(E().meth(5), "E(5)D(5)C(5)B(5)A(5)")

    class F(E):
        def meth(self, a):
            s = self.__super
            return "F(%r)[%s]" % (a, s.__class__.__name__) + s.meth(a)
    F._F__super = mysuper(F)

    vereq(F().meth(6), "F(6)[mysuper]E(6)D(6)C(6)B(6)A(6)")

    # Make sure certain errors are raised

    try:
        super(D, 42)
    except TypeError:
        pass
    else:
        raise TestFailed, "shouldn't allow super(D, 42)"

    try:
        super(D, C())
    except TypeError:
        pass
    else:
        raise TestFailed, "shouldn't allow super(D, C())"

    try:
        super(D).__get__(12)
    except TypeError:
        pass
    else:
        raise TestFailed, "shouldn't allow super(D).__get__(12)"

    try:
        super(D).__get__(C())
    except TypeError:
        pass
    else:
        raise TestFailed, "shouldn't allow super(D).__get__(C())"

def inherits():
    if verbose: print "Testing inheritance from basic types..."

    class hexint(int):
        def __repr__(self):
            return hex(self)
        def __add__(self, other):
            return hexint(int.__add__(self, other))
        # (Note that overriding __radd__ doesn't work,
        # because the int type gets first dibs.)
    vereq(repr(hexint(7) + 9), "0x10")
    vereq(repr(hexint(1000) + 7), "0x3ef")
    a = hexint(12345)
    vereq(a, 12345)
    vereq(int(a), 12345)
    verify(int(a).__class__ is int)
    vereq(hash(a), hash(12345))
    verify((+a).__class__ is int)
    verify((a >> 0).__class__ is int)
    verify((a << 0).__class__ is int)
    verify((hexint(0) << 12).__class__ is int)
    verify((hexint(0) >> 12).__class__ is int)

    class octlong(long):
        __slots__ = []
        def __str__(self):
            s = oct(self)
            if s[-1] == 'L':
                s = s[:-1]
            return s
        def __add__(self, other):
            return self.__class__(super(octlong, self).__add__(other))
        __radd__ = __add__
    vereq(str(octlong(3) + 5), "010")
    # (Note that overriding __radd__ here only seems to work
    # because the example uses a short int left argument.)
    vereq(str(5 + octlong(3000)), "05675")
    a = octlong(12345)
    vereq(a, 12345L)
    vereq(long(a), 12345L)
    vereq(hash(a), hash(12345L))
    verify(long(a).__class__ is long)
    verify((+a).__class__ is long)
    verify((-a).__class__ is long)
    verify((-octlong(0)).__class__ is long)
    verify((a >> 0).__class__ is long)
    verify((a << 0).__class__ is long)
    verify((a - 0).__class__ is long)
    verify((a * 1).__class__ is long)
    verify((a ** 1).__class__ is long)
    verify((a // 1).__class__ is long)
    verify((1 * a).__class__ is long)
    verify((a | 0).__class__ is long)
    verify((a ^ 0).__class__ is long)
    verify((a & -1L).__class__ is long)
    verify((octlong(0) << 12).__class__ is long)
    verify((octlong(0) >> 12).__class__ is long)
    verify(abs(octlong(0)).__class__ is long)

    # Because octlong overrides __add__, we can't check the absence of +0
    # optimizations using octlong.
    class longclone(long):
        pass
    a = longclone(1)
    verify((a + 0).__class__ is long)
    verify((0 + a).__class__ is long)

    class precfloat(float):
        __slots__ = ['prec']
        def __init__(self, value=0.0, prec=12):
            self.prec = int(prec)
            float.__init__(value)
        def __repr__(self):
            return "%.*g" % (self.prec, self)
    vereq(repr(precfloat(1.1)), "1.1")
    a = precfloat(12345)
    vereq(a, 12345.0)
    vereq(float(a), 12345.0)
    verify(float(a).__class__ is float)
    vereq(hash(a), hash(12345.0))
    verify((+a).__class__ is float)

    class madcomplex(complex):
        def __repr__(self):
            return "%.17gj%+.17g" % (self.imag, self.real)
    a = madcomplex(-3, 4)
    vereq(repr(a), "4j-3")
    base = complex(-3, 4)
    veris(base.__class__, complex)
    vereq(a, base)
    vereq(complex(a), base)
    veris(complex(a).__class__, complex)
    a = madcomplex(a)  # just trying another form of the constructor
    vereq(repr(a), "4j-3")
    vereq(a, base)
    vereq(complex(a), base)
    veris(complex(a).__class__, complex)
    vereq(hash(a), hash(base))
    veris((+a).__class__, complex)
    veris((a + 0).__class__, complex)
    vereq(a + 0, base)
    veris((a - 0).__class__, complex)
    vereq(a - 0, base)
    veris((a * 1).__class__, complex)
    vereq(a * 1, base)
    veris((a / 1).__class__, complex)
    vereq(a / 1, base)

    class madtuple(tuple):
        _rev = None
        def rev(self):
            if self._rev is not None:
                return self._rev
            L = list(self)
            L.reverse()
            self._rev = self.__class__(L)
            return self._rev
    a = madtuple((1,2,3,4,5,6,7,8,9,0))
    vereq(a, (1,2,3,4,5,6,7,8,9,0))
    vereq(a.rev(), madtuple((0,9,8,7,6,5,4,3,2,1)))
    vereq(a.rev().rev(), madtuple((1,2,3,4,5,6,7,8,9,0)))
    for i in range(512):
        t = madtuple(range(i))
        u = t.rev()
        v = u.rev()
        vereq(v, t)
    a = madtuple((1,2,3,4,5))
    vereq(tuple(a), (1,2,3,4,5))
    verify(tuple(a).__class__ is tuple)
    vereq(hash(a), hash((1,2,3,4,5)))
    verify(a[:].__class__ is tuple)
    verify((a * 1).__class__ is tuple)
    verify((a * 0).__class__ is tuple)
    verify((a + ()).__class__ is tuple)
    a = madtuple(())
    vereq(tuple(a), ())
    verify(tuple(a).__class__ is tuple)
    verify((a + a).__class__ is tuple)
    verify((a * 0).__class__ is tuple)
    verify((a * 1).__class__ is tuple)
    verify((a * 2).__class__ is tuple)
    verify(a[:].__class__ is tuple)

    class madstring(str):
        _rev = None
        def rev(self):
            if self._rev is not None:
                return self._rev
            L = list(self)
            L.reverse()
            self._rev = self.__class__("".join(L))
            return self._rev
    s = madstring("abcdefghijklmnopqrstuvwxyz")
    vereq(s, "abcdefghijklmnopqrstuvwxyz")
    vereq(s.rev(), madstring("zyxwvutsrqponmlkjihgfedcba"))
    vereq(s.rev().rev(), madstring("abcdefghijklmnopqrstuvwxyz"))
    for i in range(256):
        s = madstring("".join(map(chr, range(i))))
        t = s.rev()
        u = t.rev()
        vereq(u, s)
    s = madstring("12345")
    vereq(str(s), "12345")
    verify(str(s).__class__ is str)

    base = "\x00" * 5
    s = madstring(base)
    vereq(s, base)
    vereq(str(s), base)
    verify(str(s).__class__ is str)
    vereq(hash(s), hash(base))
    vereq({s: 1}[base], 1)
    vereq({base: 1}[s], 1)
    verify((s + "").__class__ is str)
    vereq(s + "", base)
    verify(("" + s).__class__ is str)
    vereq("" + s, base)
    verify((s * 0).__class__ is str)
    vereq(s * 0, "")
    verify((s * 1).__class__ is str)
    vereq(s * 1, base)
    verify((s * 2).__class__ is str)
    vereq(s * 2, base + base)
    verify(s[:].__class__ is str)
    vereq(s[:], base)
    verify(s[0:0].__class__ is str)
    vereq(s[0:0], "")
    verify(s.strip().__class__ is str)
    vereq(s.strip(), base)
    verify(s.lstrip().__class__ is str)
    vereq(s.lstrip(), base)
    verify(s.rstrip().__class__ is str)
    vereq(s.rstrip(), base)
    identitytab = ''.join([chr(i) for i in range(256)])
    verify(s.translate(identitytab).__class__ is str)
    vereq(s.translate(identitytab), base)
    verify(s.translate(identitytab, "x").__class__ is str)
    vereq(s.translate(identitytab, "x"), base)
    vereq(s.translate(identitytab, "\x00"), "")
    verify(s.replace("x", "x").__class__ is str)
    vereq(s.replace("x", "x"), base)
    verify(s.ljust(len(s)).__class__ is str)
    vereq(s.ljust(len(s)), base)
    verify(s.rjust(len(s)).__class__ is str)
    vereq(s.rjust(len(s)), base)
    verify(s.center(len(s)).__class__ is str)
    vereq(s.center(len(s)), base)
    verify(s.lower().__class__ is str)
    vereq(s.lower(), base)

    s = madstring("x y")
    vereq(s, "x y")
    verify(intern(s).__class__ is str)
    verify(intern(s) is intern("x y"))
    vereq(intern(s), "x y")

    i = intern("y x")
    s = madstring("y x")
    vereq(s, i)
    verify(intern(s).__class__ is str)
    verify(intern(s) is i)

    s = madstring(i)
    verify(intern(s).__class__ is str)
    verify(intern(s) is i)

    class madunicode(unicode):
        _rev = None
        def rev(self):
            if self._rev is not None:
                return self._rev
            L = list(self)
            L.reverse()
            self._rev = self.__class__(u"".join(L))
            return self._rev
    u = madunicode("ABCDEF")
    vereq(u, u"ABCDEF")
    vereq(u.rev(), madunicode(u"FEDCBA"))
    vereq(u.rev().rev(), madunicode(u"ABCDEF"))
    base = u"12345"
    u = madunicode(base)
    vereq(unicode(u), base)
    verify(unicode(u).__class__ is unicode)
    vereq(hash(u), hash(base))
    vereq({u: 1}[base], 1)
    vereq({base: 1}[u], 1)
    verify(u.strip().__class__ is unicode)
    vereq(u.strip(), base)
    verify(u.lstrip().__class__ is unicode)
    vereq(u.lstrip(), base)
    verify(u.rstrip().__class__ is unicode)
    vereq(u.rstrip(), base)
    verify(u.replace(u"x", u"x").__class__ is unicode)
    vereq(u.replace(u"x", u"x"), base)
    verify(u.replace(u"xy", u"xy").__class__ is unicode)
    vereq(u.replace(u"xy", u"xy"), base)
    verify(u.center(len(u)).__class__ is unicode)
    vereq(u.center(len(u)), base)
    verify(u.ljust(len(u)).__class__ is unicode)
    vereq(u.ljust(len(u)), base)
    verify(u.rjust(len(u)).__class__ is unicode)
    vereq(u.rjust(len(u)), base)
    verify(u.lower().__class__ is unicode)
    vereq(u.lower(), base)
    verify(u.upper().__class__ is unicode)
    vereq(u.upper(), base)
    verify(u.capitalize().__class__ is unicode)
    vereq(u.capitalize(), base)
    verify(u.title().__class__ is unicode)
    vereq(u.title(), base)
    verify((u + u"").__class__ is unicode)
    vereq(u + u"", base)
    verify((u"" + u).__class__ is unicode)
    vereq(u"" + u, base)
    verify((u * 0).__class__ is unicode)
    vereq(u * 0, u"")
    verify((u * 1).__class__ is unicode)
    vereq(u * 1, base)
    verify((u * 2).__class__ is unicode)
    vereq(u * 2, base + base)
    verify(u[:].__class__ is unicode)
    vereq(u[:], base)
    verify(u[0:0].__class__ is unicode)
    vereq(u[0:0], u"")

    class sublist(list):
        pass
    a = sublist(range(5))
    vereq(a, range(5))
    a.append("hello")
    vereq(a, range(5) + ["hello"])
    a[5] = 5
    vereq(a, range(6))
    a.extend(range(6, 20))
    vereq(a, range(20))
    a[-5:] = []
    vereq(a, range(15))
    del a[10:15]
    vereq(len(a), 10)
    vereq(a, range(10))
    vereq(list(a), range(10))
    vereq(a[0], 0)
    vereq(a[9], 9)
    vereq(a[-10], 0)
    vereq(a[-1], 9)
    vereq(a[:5], range(5))

    class CountedInput(file):
        """Counts lines read by self.readline().

        self.lineno is the 0-based ordinal of the last line read, up to
        a maximum of one greater than the number of lines in the file.

        self.ateof is true if and only if the final "" line has been read,
        at which point self.lineno stops incrementing, and further calls
        to readline() continue to return "".
        """

        lineno = 0
        ateof = 0
        def readline(self):
            if self.ateof:
                return ""
            s = file.readline(self)
            # Next line works too.
            # s = super(CountedInput, self).readline()
            self.lineno += 1
            if s == "":
                self.ateof = 1
            return s

    f = file(name=TESTFN, mode='w')
    lines = ['a\n', 'b\n', 'c\n']
    try:
        f.writelines(lines)
        f.close()
        f = CountedInput(TESTFN)
        for (i, expected) in zip(range(1, 5) + [4], lines + 2 * [""]):
            got = f.readline()
            vereq(expected, got)
            vereq(f.lineno, i)
            vereq(f.ateof, (i > len(lines)))
        f.close()
    finally:
        try:
            f.close()
        except:
            pass
        try:
            import os
            os.unlink(TESTFN)
        except:
            pass

def keywords():
    if verbose:
        print "Testing keyword args to basic type constructors ..."
    vereq(int(x=1), 1)
    vereq(float(x=2), 2.0)
    vereq(long(x=3), 3L)
    vereq(complex(imag=42, real=666), complex(666, 42))
    vereq(str(object=500), '500')
    vereq(unicode(string='abc', errors='strict'), u'abc')
    vereq(tuple(sequence=range(3)), (0, 1, 2))
    vereq(list(sequence=(0, 1, 2)), range(3))
    vereq(dict(items={1: 2}), {1: 2})

    for constructor in (int, float, long, complex, str, unicode,
                        tuple, list, dict, file):
        try:
            constructor(bogus_keyword_arg=1)
        except TypeError:
            pass
        else:
            raise TestFailed("expected TypeError from bogus keyword "
                             "argument to %r" % constructor)

def restricted():
    import rexec
    if verbose:
        print "Testing interaction with restricted execution ..."

    sandbox = rexec.RExec()

    code1 = """f = open(%r, 'w')""" % TESTFN
    code2 = """f = file(%r, 'w')""" % TESTFN
    code3 = """\
f = open(%r)
t = type(f)  # a sneaky way to get the file() constructor
f.close()
f = t(%r, 'w')  # rexec can't catch this by itself
""" % (TESTFN, TESTFN)

    f = open(TESTFN, 'w')  # Create the file so code3 can find it.
    f.close()

    try:
        for code in code1, code2, code3:
            try:
                sandbox.r_exec(code)
            except IOError, msg:
                if str(msg).find("restricted") >= 0:
                    outcome = "OK"
                else:
                    outcome = "got an exception, but not an expected one"
            else:
                outcome = "expected a restricted-execution exception"

            if outcome != "OK":
                raise TestFailed("%s, in %r" % (outcome, code))

    finally:
        try:
            import os
            os.unlink(TESTFN)
        except:
            pass

def str_subclass_as_dict_key():
    if verbose:
        print "Testing a str subclass used as dict key .."

    class cistr(str):
        """Sublcass of str that computes __eq__ case-insensitively.

        Also computes a hash code of the string in canonical form.
        """

        def __init__(self, value):
            self.canonical = value.lower()
            self.hashcode = hash(self.canonical)

        def __eq__(self, other):
            if not isinstance(other, cistr):
                other = cistr(other)
            return self.canonical == other.canonical

        def __hash__(self):
            return self.hashcode

    vereq(cistr('ABC'), 'abc')
    vereq('aBc', cistr('ABC'))
    vereq(str(cistr('ABC')), 'ABC')

    d = {cistr('one'): 1, cistr('two'): 2, cistr('tHree'): 3}
    vereq(d[cistr('one')], 1)
    vereq(d[cistr('tWo')], 2)
    vereq(d[cistr('THrEE')], 3)
    verify(cistr('ONe') in d)
    vereq(d.get(cistr('thrEE')), 3)

def classic_comparisons():
    if verbose: print "Testing classic comparisons..."
    class classic:
        pass
    for base in (classic, int, object):
        if verbose: print "        (base = %s)" % base
        class C(base):
            def __init__(self, value):
                self.value = int(value)
            def __cmp__(self, other):
                if isinstance(other, C):
                    return cmp(self.value, other.value)
                if isinstance(other, int) or isinstance(other, long):
                    return cmp(self.value, other)
                return NotImplemented
        c1 = C(1)
        c2 = C(2)
        c3 = C(3)
        vereq(c1, 1)
        c = {1: c1, 2: c2, 3: c3}
        for x in 1, 2, 3:
            for y in 1, 2, 3:
                verify(cmp(c[x], c[y]) == cmp(x, y), "x=%d, y=%d" % (x, y))
                for op in "<", "<=", "==", "!=", ">", ">=":
                    verify(eval("c[x] %s c[y]" % op) == eval("x %s y" % op),
                           "x=%d, y=%d" % (x, y))
                verify(cmp(c[x], y) == cmp(x, y), "x=%d, y=%d" % (x, y))
                verify(cmp(x, c[y]) == cmp(x, y), "x=%d, y=%d" % (x, y))

def rich_comparisons():
    if verbose:
        print "Testing rich comparisons..."
    class Z(complex):
        pass
    z = Z(1)
    vereq(z, 1+0j)
    vereq(1+0j, z)
    class ZZ(complex):
        def __eq__(self, other):
            try:
                return abs(self - other) <= 1e-6
            except:
                return NotImplemented
    zz = ZZ(1.0000003)
    vereq(zz, 1+0j)
    vereq(1+0j, zz)

    class classic:
        pass
    for base in (classic, int, object, list):
        if verbose: print "        (base = %s)" % base
        class C(base):
            def __init__(self, value):
                self.value = int(value)
            def __cmp__(self, other):
                raise TestFailed, "shouldn't call __cmp__"
            def __eq__(self, other):
                if isinstance(other, C):
                    return self.value == other.value
                if isinstance(other, int) or isinstance(other, long):
                    return self.value == other
                return NotImplemented
            def __ne__(self, other):
                if isinstance(other, C):
                    return self.value != other.value
                if isinstance(other, int) or isinstance(other, long):
                    return self.value != other
                return NotImplemented
            def __lt__(self, other):
                if isinstance(other, C):
                    return self.value < other.value
                if isinstance(other, int) or isinstance(other, long):
                    return self.value < other
                return NotImplemented
            def __le__(self, other):
                if isinstance(other, C):
                    return self.value <= other.value
                if isinstance(other, int) or isinstance(other, long):
                    return self.value <= other
                return NotImplemented
            def __gt__(self, other):
                if isinstance(other, C):
                    return self.value > other.value
                if isinstance(other, int) or isinstance(other, long):
                    return self.value > other
                return NotImplemented
            def __ge__(self, other):
                if isinstance(other, C):
                    return self.value >= other.value
                if isinstance(other, int) or isinstance(other, long):
                    return self.value >= other
                return NotImplemented
        c1 = C(1)
        c2 = C(2)
        c3 = C(3)
        vereq(c1, 1)
        c = {1: c1, 2: c2, 3: c3}
        for x in 1, 2, 3:
            for y in 1, 2, 3:
                for op in "<", "<=", "==", "!=", ">", ">=":
                    verify(eval("c[x] %s c[y]" % op) == eval("x %s y" % op),
                           "x=%d, y=%d" % (x, y))
                    verify(eval("c[x] %s y" % op) == eval("x %s y" % op),
                           "x=%d, y=%d" % (x, y))
                    verify(eval("x %s c[y]" % op) == eval("x %s y" % op),
                           "x=%d, y=%d" % (x, y))

def coercions():
    if verbose: print "Testing coercions..."
    class I(int): pass
    coerce(I(0), 0)
    coerce(0, I(0))
    class L(long): pass
    coerce(L(0), 0)
    coerce(L(0), 0L)
    coerce(0, L(0))
    coerce(0L, L(0))
    class F(float): pass
    coerce(F(0), 0)
    coerce(F(0), 0L)
    coerce(F(0), 0.)
    coerce(0, F(0))
    coerce(0L, F(0))
    coerce(0., F(0))
    class C(complex): pass
    coerce(C(0), 0)
    coerce(C(0), 0L)
    coerce(C(0), 0.)
    coerce(C(0), 0j)
    coerce(0, C(0))
    coerce(0L, C(0))
    coerce(0., C(0))
    coerce(0j, C(0))

def descrdoc():
    if verbose: print "Testing descriptor doc strings..."
    def check(descr, what):
        vereq(descr.__doc__, what)
    check(file.closed, "flag set if the file is closed") # getset descriptor
    check(file.name, "file name") # member descriptor

def setclass():
    if verbose: print "Testing __class__ assignment..."
    class C(object): pass
    class D(object): pass
    class E(object): pass
    class F(D, E): pass
    for cls in C, D, E, F:
        for cls2 in C, D, E, F:
            x = cls()
            x.__class__ = cls2
            verify(x.__class__ is cls2)
            x.__class__ = cls
            verify(x.__class__ is cls)
    def cant(x, C):
        try:
            x.__class__ = C
        except TypeError:
            pass
        else:
            raise TestFailed, "shouldn't allow %r.__class__ = %r" % (x, C)
    cant(C(), list)
    cant(list(), C)
    cant(C(), 1)
    cant(C(), object)
    cant(object(), list)
    cant(list(), object)

def setdict():
    if verbose: print "Testing __dict__ assignment..."
    class C(object): pass
    a = C()
    a.__dict__ = {'b': 1}
    vereq(a.b, 1)
    def cant(x, dict):
        try:
            x.__dict__ = dict
        except TypeError:
            pass
        else:
            raise TestFailed, "shouldn't allow %r.__dict__ = %r" % (x, dict)
    cant(a, None)
    cant(a, [])
    cant(a, 1)
    del a.__dict__ # Deleting __dict__ is allowed
    # Classes don't allow __dict__ assignment
    cant(C, {})

def pickles():
    if verbose:
        print "Testing pickling and copying new-style classes and objects..."
    import pickle, cPickle

    def sorteditems(d):
        L = d.items()
        L.sort()
        return L

    global C
    class C(object):
        def __init__(self, a, b):
            super(C, self).__init__()
            self.a = a
            self.b = b
        def __repr__(self):
            return "C(%r, %r)" % (self.a, self.b)

    global C1
    class C1(list):
        def __new__(cls, a, b):
            return super(C1, cls).__new__(cls)
        def __init__(self, a, b):
            self.a = a
            self.b = b
        def __repr__(self):
            return "C1(%r, %r)<%r>" % (self.a, self.b, list(self))

    global C2
    class C2(int):
        def __new__(cls, a, b, val=0):
            return super(C2, cls).__new__(cls, val)
        def __init__(self, a, b, val=0):
            self.a = a
            self.b = b
        def __repr__(self):
            return "C2(%r, %r)<%r>" % (self.a, self.b, int(self))

    global C3
    class C3(object):
        def __init__(self, foo):
            self.foo = foo
        def __getstate__(self):
            return self.foo
        def __setstate__(self, foo):
            self.foo = foo

    global C4classic, C4
    class C4classic: # classic
        pass
    class C4(C4classic, object): # mixed inheritance
        pass

    for p in pickle, cPickle:
        for bin in 0, 1:
            if verbose:
                print p.__name__, ["text", "binary"][bin]

            for cls in C, C1, C2:
                s = p.dumps(cls, bin)
                cls2 = p.loads(s)
                verify(cls2 is cls)

            a = C1(1, 2); a.append(42); a.append(24)
            b = C2("hello", "world", 42)
            s = p.dumps((a, b), bin)
            x, y = p.loads(s)
            vereq(x.__class__, a.__class__)
            vereq(sorteditems(x.__dict__), sorteditems(a.__dict__))
            vereq(y.__class__, b.__class__)
            vereq(sorteditems(y.__dict__), sorteditems(b.__dict__))
            vereq(`x`, `a`)
            vereq(`y`, `b`)
            if verbose:
                print "a = x =", a
                print "b = y =", b
            # Test for __getstate__ and __setstate__ on new style class
            u = C3(42)
            s = p.dumps(u, bin)
            v = p.loads(s)
            veris(u.__class__, v.__class__)
            vereq(u.foo, v.foo)
            # Test for picklability of hybrid class
            u = C4()
            u.foo = 42
            s = p.dumps(u, bin)
            v = p.loads(s)
            veris(u.__class__, v.__class__)
            vereq(u.foo, v.foo)

    # Testing copy.deepcopy()
    if verbose:
        print "deepcopy"
    import copy
    for cls in C, C1, C2:
        cls2 = copy.deepcopy(cls)
        verify(cls2 is cls)

    a = C1(1, 2); a.append(42); a.append(24)
    b = C2("hello", "world", 42)
    x, y = copy.deepcopy((a, b))
    vereq(x.__class__, a.__class__)
    vereq(sorteditems(x.__dict__), sorteditems(a.__dict__))
    vereq(y.__class__, b.__class__)
    vereq(sorteditems(y.__dict__), sorteditems(b.__dict__))
    vereq(`x`, `a`)
    vereq(`y`, `b`)
    if verbose:
        print "a = x =", a
        print "b = y =", b

def copies():
    if verbose: print "Testing copy.copy() and copy.deepcopy()..."
    import copy
    class C(object):
        pass

    a = C()
    a.foo = 12
    b = copy.copy(a)
    vereq(b.__dict__, a.__dict__)

    a.bar = [1,2,3]
    c = copy.copy(a)
    vereq(c.bar, a.bar)
    verify(c.bar is a.bar)

    d = copy.deepcopy(a)
    vereq(d.__dict__, a.__dict__)
    a.bar.append(4)
    vereq(d.bar, [1,2,3])

def binopoverride():
    if verbose: print "Testing overrides of binary operations..."
    class I(int):
        def __repr__(self):
            return "I(%r)" % int(self)
        def __add__(self, other):
            return I(int(self) + int(other))
        __radd__ = __add__
        def __pow__(self, other, mod=None):
            if mod is None:
                return I(pow(int(self), int(other)))
            else:
                return I(pow(int(self), int(other), int(mod)))
        def __rpow__(self, other, mod=None):
            if mod is None:
                return I(pow(int(other), int(self), mod))
            else:
                return I(pow(int(other), int(self), int(mod)))

    vereq(`I(1) + I(2)`, "I(3)")
    vereq(`I(1) + 2`, "I(3)")
    vereq(`1 + I(2)`, "I(3)")
    vereq(`I(2) ** I(3)`, "I(8)")
    vereq(`2 ** I(3)`, "I(8)")
    vereq(`I(2) ** 3`, "I(8)")
    vereq(`pow(I(2), I(3), I(5))`, "I(3)")
    class S(str):
        def __eq__(self, other):
            return self.lower() == other.lower()

def subclasspropagation():
    if verbose: print "Testing propagation of slot functions to subclasses..."
    class A(object):
        pass
    class B(A):
        pass
    class C(A):
        pass
    class D(B, C):
        pass
    d = D()
    vereq(hash(d), id(d))
    A.__hash__ = lambda self: 42
    vereq(hash(d), 42)
    C.__hash__ = lambda self: 314
    vereq(hash(d), 314)
    B.__hash__ = lambda self: 144
    vereq(hash(d), 144)
    D.__hash__ = lambda self: 100
    vereq(hash(d), 100)
    del D.__hash__
    vereq(hash(d), 144)
    del B.__hash__
    vereq(hash(d), 314)
    del C.__hash__
    vereq(hash(d), 42)
    del A.__hash__
    vereq(hash(d), id(d))
    d.foo = 42
    d.bar = 42
    vereq(d.foo, 42)
    vereq(d.bar, 42)
    def __getattribute__(self, name):
        if name == "foo":
            return 24
        return object.__getattribute__(self, name)
    A.__getattribute__ = __getattribute__
    vereq(d.foo, 24)
    vereq(d.bar, 42)
    def __getattr__(self, name):
        if name in ("spam", "foo", "bar"):
            return "hello"
        raise AttributeError, name
    B.__getattr__ = __getattr__
    vereq(d.spam, "hello")
    vereq(d.foo, 24)
    vereq(d.bar, 42)
    del A.__getattribute__
    vereq(d.foo, 42)
    del d.foo
    vereq(d.foo, "hello")
    vereq(d.bar, 42)
    del B.__getattr__
    try:
        d.foo
    except AttributeError:
        pass
    else:
        raise TestFailed, "d.foo should be undefined now"

def buffer_inherit():
    import binascii
    # SF bug [#470040] ParseTuple t# vs subclasses.
    if verbose:
        print "Testing that buffer interface is inherited ..."

    class MyStr(str):
        pass
    base = 'abc'
    m = MyStr(base)
    # b2a_hex uses the buffer interface to get its argument's value, via
    # PyArg_ParseTuple 't#' code.
    vereq(binascii.b2a_hex(m), binascii.b2a_hex(base))

    # It's not clear that unicode will continue to support the character
    # buffer interface, and this test will fail if that's taken away.
    class MyUni(unicode):
        pass
    base = u'abc'
    m = MyUni(base)
    vereq(binascii.b2a_hex(m), binascii.b2a_hex(base))

    class MyInt(int):
        pass
    m = MyInt(42)
    try:
        binascii.b2a_hex(m)
        raise TestFailed('subclass of int should not have a buffer interface')
    except TypeError:
        pass

def str_of_str_subclass():
    import binascii
    import cStringIO

    if verbose:
        print "Testing __str__ defined in subclass of str ..."

    class octetstring(str):
        def __str__(self):
            return binascii.b2a_hex(self)
        def __repr__(self):
            return self + " repr"

    o = octetstring('A')
    vereq(type(o), octetstring)
    vereq(type(str(o)), str)
    vereq(type(repr(o)), str)
    vereq(ord(o), 0x41)
    vereq(str(o), '41')
    vereq(repr(o), 'A repr')
    vereq(o.__str__(), '41')
    vereq(o.__repr__(), 'A repr')

    capture = cStringIO.StringIO()
    # Calling str() or not exercises different internal paths.
    print >> capture, o
    print >> capture, str(o)
    vereq(capture.getvalue(), '41\n41\n')
    capture.close()

def kwdargs():
    if verbose: print "Testing keyword arguments to __init__, __call__..."
    def f(a): return a
    vereq(f.__call__(a=42), 42)
    a = []
    list.__init__(a, sequence=[0, 1, 2])
    vereq(a, [0, 1, 2])

def delhook():
    if verbose: print "Testing __del__ hook..."
    log = []
    class C(object):
        def __del__(self):
            log.append(1)
    c = C()
    vereq(log, [])
    del c
    vereq(log, [1])

    class D(object): pass
    d = D()
    try: del d[0]
    except TypeError: pass
    else: raise TestFailed, "invalid del() didn't raise TypeError"

def hashinherit():
    if verbose: print "Testing hash of mutable subclasses..."

    class mydict(dict):
        pass
    d = mydict()
    try:
        hash(d)
    except TypeError:
        pass
    else:
        raise TestFailed, "hash() of dict subclass should fail"

    class mylist(list):
        pass
    d = mylist()
    try:
        hash(d)
    except TypeError:
        pass
    else:
        raise TestFailed, "hash() of list subclass should fail"

def strops():
    try: 'a' + 5
    except TypeError: pass
    else: raise TestFailed, "'' + 5 doesn't raise TypeError"

    try: ''.split('')
    except ValueError: pass
    else: raise TestFailed, "''.split('') doesn't raise ValueError"

    try: ''.join([0])
    except TypeError: pass
    else: raise TestFailed, "''.join([0]) doesn't raise TypeError"

    try: ''.rindex('5')
    except ValueError: pass
    else: raise TestFailed, "''.rindex('5') doesn't raise ValueError"

    try: ''.replace('', '')
    except ValueError: pass
    else: raise TestFailed, "''.replace('', '') doesn't raise ValueError"

    try: '%(n)s' % None
    except TypeError: pass
    else: raise TestFailed, "'%(n)s' % None doesn't raise TypeError"

    try: '%(n' % {}
    except ValueError: pass
    else: raise TestFailed, "'%(n' % {} '' doesn't raise ValueError"

    try: '%*s' % ('abc')
    except TypeError: pass
    else: raise TestFailed, "'%*s' % ('abc') doesn't raise TypeError"

    try: '%*.*s' % ('abc', 5)
    except TypeError: pass
    else: raise TestFailed, "'%*.*s' % ('abc', 5) doesn't raise TypeError"

    try: '%s' % (1, 2)
    except TypeError: pass
    else: raise TestFailed, "'%s' % (1, 2) doesn't raise TypeError"

    try: '%' % None
    except ValueError: pass
    else: raise TestFailed, "'%' % None doesn't raise ValueError"

    vereq('534253'.isdigit(), 1)
    vereq('534253x'.isdigit(), 0)
    vereq('%c' % 5, '\x05')
    vereq('%c' % '5', '5')




def test_main():
    class_docstrings()
    lists()
    dicts()
    dict_constructor()
    test_dir()
    ints()
    longs()
    floats()
    complexes()
    spamlists()
    spamdicts()
    pydicts()
    pylists()
    metaclass()
    pymods()
    multi()
    diamond()
    objects()
    slots()
    dynamics()
    errors()
    classmethods()
    staticmethods()
    classic()
    compattr()
    newslot()
    altmro()
    overloading()
    methods()
    specials()
    weakrefs()
    properties()
    supers()
    inherits()
    keywords()
    restricted()
    str_subclass_as_dict_key()
    classic_comparisons()
    rich_comparisons()
    coercions()
    descrdoc()
    setclass()
    setdict()
    pickles()
    copies()
    binopoverride()
    subclasspropagation()
    buffer_inherit()
    str_of_str_subclass()
    kwdargs()
    delhook()
    hashinherit()
    strops()
    if verbose: print "All OK"

if __name__ == "__main__":
    test_main()
