def fibo(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fibo(n - 1) + fibo(n - 2)

def mark_bytecode(path):
    inst_count = 0
    marked_lines = []
    with open(path, "r") as f:
        bytecode = f.readlines()

    for l in bytecode:
        if l.strip():
            marked_lines.append(f'{inst_count}: {l.strip()}\n')
            inst_count += 1
        else:
            marked_lines.append('\n')
    with open(path + "_marked", "w") as f:
        f.writelines(marked_lines)

# print(fibo(6))
mark_bytecode('/home/varvara/projects/vm_course/benchmarks/' + 'rec')



