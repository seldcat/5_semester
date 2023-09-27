def check(x: str, file: str):
    strs = list(map(lambda el: el.lower(), x.split()))
    unique = sorted(set(strs))
    with open(file, 'w') as file:
        for elem in unique:
            file.write(f'{elem} {strs.count(elem)}\n')
