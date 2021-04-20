import subprocess
import time
import os, os.path
import matplotlib.pyplot as plt

with open('entradas-busca-local/in-0.txt') as f:
    start = time.perf_counter()
    proc = subprocess.run(['./busca-local-1'],
                          input=f.read(),
                          text=True,
                          capture_output=True)
    end = time.perf_counter()

    print('Saida:', proc.stdout)
    print('Stderr:', proc.stderr)
    print('Tempo total(s):', end - start)


def roda_com_entrada(executavel, arquivo_in):
    tempo = []
    with open('entradas-busca-local/' + arquivo_in) as f:
        start = time.perf_counter()
        proc = subprocess.run(['./' + executavel],
                              input=f.read(),
                              text=True,
                              capture_output=True)
        end = time.perf_counter()

        # print('Saida:', proc.stdout)
        # print('Stderr:', proc.stderr)
        # print('Tempo total(s):', end - start)
    tempo.append(end-start)
    return tempo

def get_size(arquivo_in):
    tamanho = []
    with open('entradas-busca-local/' +arquivo_in, "r") as f:
        lines = f.readlines()
        tamanho.append(int(lines[0]))
    print(tamanho)    
    return tamanho    


i = 0
tam = []
r1 = []
r2 = []
r1_par = []
r2_par = []
while i < 9:
    r1.append(roda_com_entrada("busca-local-1", f"in-{i}.txt"))
    r2.append(roda_com_entrada("busca-local-2", f"in-{i}.txt"))
    r1_par.append(roda_com_entrada("busca-local-1-par", f"in-{i}.txt"))
    r2_par.append(roda_com_entrada("busca-local-2-par", f"in-{i}.txt"))
    tam.append(get_size(f"in-{i}.txt"))
    i+=1

plt.plot(tam, r1, "-b", label="busca-local-1")
plt.plot(tam, r1_par, "-r", label="busca-local-1-par")
plt.plot(tam, r2, "-g", label="busca-local-2")
plt.plot(tam, r2_par, "-y", label="busca-local-2-par")
plt.legend(loc="upper left")
plt.xlabel("Length of list (number)")
plt.ylabel("Time taken (seconds)")
plt.savefig('grafico')