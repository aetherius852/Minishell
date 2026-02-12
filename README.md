# 🐚 Minishell

**Tan bonito como shell**

Un shell sencillo implementado en C que recrea la funcionalidad básica de bash.

---

## 📋 Descripción

Minishell es un proyecto que consiste en crear un intérprete de línea de comandos funcional, similar a bash. Este proyecto permite comprender en profundidad cómo funcionan los procesos, los file descriptors y la ejecución de comandos en Unix.

---

## ✨ Funcionalidades

### Características Principales

- ✅ Prompt interactivo que espera comandos
- ✅ Historial de comandos funcional
- ✅ Búsqueda y ejecución de ejecutables (PATH, rutas relativas/absolutas)
- ✅ Gestión de señales (`ctrl-C`, `ctrl-D`, `ctrl-\`)

### Redirecciones

- `<` - Redirección de entrada
- `>` - Redirección de salida
- `<<` - Here-doc (delimitador)
- `>>` - Redirección de salida en modo append

### Pipes

- `|` - Conexión de comandos mediante pipes

### Variables de Entorno

- `$VARIABLE` - Expansión de variables de entorno
- `$?` - Estado de salida del último comando ejecutado

### Comillas

- `'` - Comillas simples (evita interpretación de metacaracteres)
- `"` - Comillas dobles (evita interpretación excepto `$`)

### Built-ins Implementados

| Comando | Descripción |
|---------|-------------|
| `echo` | Imprime texto (con opción `-n`) |
| `cd` | Cambia de directorio (ruta relativa o absoluta) |
| `pwd` | Muestra el directorio actual |
| `export` | Exporta variables de entorno |
| `unset` | Elimina variables de entorno |
| `env` | Muestra las variables de entorno |
| `exit` | Sale del shell |

---

## 🚀 Compilación y Uso

### Compilar

```bash
make
```

### Ejecutar

```bash
./minishell
```

### Limpiar

```bash
make clean   # Elimina archivos objeto
make fclean  # Elimina archivos objeto y ejecutable
make re      # Recompila desde cero
```

---

## 🎯 Parte Bonus

### Funcionalidades Extra

- `&&` y `||` - Operadores lógicos con paréntesis para prioridades
- `*` - Wildcards para el directorio actual

> ⚠️ **Nota:** Los bonus solo se evalúan si la parte obligatoria está perfecta.

---

## 📚 Funciones Autorizadas

```
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, 
add_history, printf, malloc, free, write, access, open, read, close, fork, 
wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, 
stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, 
closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, 
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
```

---

## 📝 Norma

El proyecto sigue estrictamente la **Norma** de 42:
- Sin memory leaks (excepto los propios de `readline`)
- Sin errores de segmentación
- Compilación con flags `-Wall -Werror -Wextra`
- Uso máximo de una variable global para señales

---

## 🧪 Ejemplos de Uso

```bash
minishell$ echo "Hola Mundo"
Hola Mundo

minishell$ ls -la | grep minishell

minishell$ cat < input.txt | grep "texto" > output.txt

minishell$ export USER=estudiante

minishell$ echo $USER
estudiante

minishell$ cd /tmp && pwd
/tmp

minishell$ exit
```

---

## 🔍 Comportamiento de Señales

| Señal | Modo Interactivo | Descripción |
|-------|------------------|-------------|
| `ctrl-C` | ✅ | Muestra un nuevo prompt en una línea nueva |
| `ctrl-D` | ✅ | Termina el shell |
| `ctrl-\` | ❌ | No hace nada |

---

## 📖 Referencia

En caso de dudas sobre el comportamiento esperado, se puede utilizar **bash** como referencia.

---

## 👥 Autores

Proyecto desarrollado como parte del currículum de 42.

---

## 📄 Licencia

Este proyecto es parte del currículum educativo de 42.