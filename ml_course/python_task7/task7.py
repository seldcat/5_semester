def find_modified_max_argmax(L, f):
    r = list(map(f, filter(lambda x: type(x) is int, L)))
    if r:
        m = max(r)
        return m, r.index(m)
    return ()
