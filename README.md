# 🍜 Filosofos: El Problema de la Cena de los Filósofos 🍜

Este repositorio contiene la implementación del proyecto "Filósofos" (`Philosophers`), un ejercicio fundamental en la formación de 42 que introduce los conceptos de **programación concurrente**, **sincronización de hilos** y la gestión de **recursos compartidos**.

El proyecto aborda el clásico [Problema de la Cena de los Filósofos](https://es.wikipedia.org/wiki/Problema_de_la_cena_de_los_fil%C3%B3sofos), un escenario ideal para comprender desafíos como los **deadlocks** (interbloqueos), las **race conditions** (condiciones de carrera) y la **starvation** (inanición).

---

## 📚 Tabla de Contenidos

1.  [Filosofía de 42 y Concurrencia](#filosofía-de-42-y-concurrencia)
2.  [El Problema de la Cena de los Filósofos](#el-problema-de-la-cena-de-los-filósofos)
3.  [Conceptos Clave Aplicados](#conceptos-clave-aplicados)
4.  [Estructura y Componentes de la Implementación](#estructura-y-componentes-de-la-implementación)
    *   [Estructuras de Datos Principales](#estructuras-de-datos-principales)
    *   [Estados del Filósofo](#estados-del-filósofo)
    *   [Ciclo de Vida del Filósofo](#ciclo-de-vida-del-filósofo)
    *   [Estrategia para Evitar Deadlocks](#estrategia-para-evitar-deadlocks)
    *   [Manejo del Tiempo y Monitoreo](#manejo-del-tiempo-y-monitoreo)
5.  [Compilación y Ejecución](#compilación-y-ejecución)
6.  [Testing y Validación](#testing-y-validación)
7.  [Autor](#autor)

---

## 🎓 Filosofía de 42 y Concurrencia

En 42, los proyectos están diseñados para llevarnos al límite de la comprensión y la optimización. En el ámbito de la concurrencia, esto significa:

*   **Gestión Manual de Hilos**: Uso directo de la biblioteca POSIX Threads (`pthread`) para crear, unir y sincronizar hilos, en lugar de abstracciones de alto nivel.
*   **Sincronización Explícita**: Implementación manual de mutexes (`pthread_mutex_t`) para proteger recursos compartidos y evitar condiciones de carrera.
*   **Detección y Prevención de Problemas**: No solo se trata de hacer que el programa funcione, sino de garantizar que no ocurran deadlocks, race conditions o starvation bajo diversas condiciones de ejecución.
*   **Manejo Preciso del Tiempo**: Implementación de temporizadores para simular el paso del tiempo y verificar las condiciones de vida/muerte de los filósofos.
*   **C++98 / C11**: Aunque este proyecto se puede abordar con C o C++, las restricciones de estilo y las herramientas disponibles (como los `pthreads`) se aplican rigurosamente y su enfoque está dirigido en el lenguaje C.

---

## 🍲 El Problema de la Cena de los Filósofos

El problema, propuesto por Edsger W. Dijkstra, es el siguiente:

> N filósofos están sentados alrededor de una mesa circular. Hay un plato de fideos frente a cada filósofo y un tenedor entre cada par de filósofos. Para comer, un filósofo necesita tomar ambos tenedores adyacentes a su plato (uno a la izquierda y otro a la derecha). Los filósofos alternan entre pensar y comer.
>
> **El desafío**: Diseñar un algoritmo que permita a los filósofos comer sin caer en un deadlock (donde todos esperan por un recurso que otro tiene) o starvation (donde un filósofo nunca logra comer).

En este proyecto, cada filósofo es un hilo independiente que ejecuta un ciclo de pensar, intentar comer y dormir.

---

## 🔑 Conceptos Clave Aplicados

Para resolver este problema de manera robusta, se aplican y comprenden los siguientes conceptos:

*   **Hilos (Threads)**:
    *   `pthread_create()`: Creación de nuevos hilos de ejecución para cada filósofo y monitores.
    *   `pthread_join()`: Espera a que los hilos finalicen su ejecución.
    *   Cada filósofo es un hilo independiente que ejecuta su propio ciclo de vida.
*   **Mutexes (Exclusión Mutua)**:
    *   `pthread_mutex_init()`: Inicialización de mutexes para proteger recursos compartidos.
    *   `pthread_mutex_lock()`: Bloqueo de un mutex antes de acceder a un recurso.
    *   `pthread_mutex_unlock()`: Desbloqueo de un mutex después de usar un recurso.
    *   `pthread_mutex_destroy()`: Destrucción de mutexes al finalizar el programa.
    *   Se utilizan mutexes para:
        *   Cada tenedor individual.
        *   Proteger la salida estándar (`stdout`) para evitar mensajes de log desordenados (mutex de impresión).
        *   Proteger datos compartidos críticos como el `last_eat` de cada filósofo o los contadores de comidas.
*   **Condiciones de Carrera (Race Conditions)**: Evitadas mediante el uso adecuado de mutexes para proteger el acceso a variables compartidas que pueden ser modificadas por múltiples hilos simultáneamente.
*   **Deadlocks (Interbloqueos)**: Situación donde dos o más hilos se bloquean mutuamente, esperando indefinidamente por un recurso que el otro posee. Este proyecto requiere una estrategia explícita para prevenirlo.
*   **Starvation (Inanición)**: Situación donde un hilo nunca logra adquirir los recursos necesarios para avanzar, aunque estos estén disponibles en algún momento. La estrategia debe asegurar que todos los filósofos tengan la oportunidad de comer.
*   **Gestión del Tiempo**:
    *   `gettimeofday()` o `_gettime()` (custom): Para obtener marcas de tiempo precisas y calcular el tiempo transcurrido (ej. tiempo desde la última comida).
    *   `usleep()` / `ft_usleep()` (custom): Para simular los tiempos de comer, dormir y pensar.
*   **Monitores**: Hilos adicionales que supervisan el estado de los filósofos para detectar condiciones de muerte o si todos han comido lo suficiente.

---

## 🏗️ Estructura y Componentes de la Implementación

La implementación se basa en un diseño modular con estructuras de datos claras y funciones específicas para cada acción.

### Estructuras de Datos Principales

*   **`t_data` [6]**: Contiene la configuración global y el estado del programa.
    *   `nb_philos`: Número de filósofos.
    *   `time_to_die`: Tiempo máximo sin comer antes de morir.
    *   `time_to_eat`: Tiempo que tarda un filósofo en comer.
    *   `time_to_sleep`: Tiempo que tarda un filósofo en dormir.
    *   `nb_meals` (opcional): Número de veces que cada filósofo debe comer antes de terminar.
    *   `start_time`: El momento en que el simulador comenzó.
    *   `keep_iterating`: Un flag booleano protegido por mutex para detener todos los hilos ordenadamente.
    *   `forks`: Un array de mutexes, donde cada mutex representa un tenedor [6].
    *   `philos`: Un array de estructuras `t_philo`, una para cada filósofo.
    *   Mutexes adicionales para proteger `mut_print` (salida), `mut_keep_iter` (flag de iteración), y otras variables globales que pudieran modificarse.
*   **`t_philo` [6]**: Representa a un filósofo individual.
    *   `id`: Identificador único del filósofo.
    *   `meals`: Número de comidas que ha tomado el filósofo.
    *   `last_eat`: Timestamp de la última vez que el filósofo comió.
    *   `fork_l`, `fork_r`: Punteros a los mutexes que representan el tenedor izquierdo y derecho [6].
    *   `state`: Estado actual del filósofo (`EATING`, `SLEEPING`, `THINKING`, etc.) [6].
    *   Mutexes individuales para proteger `mut_last_eat`, `mut_num_meals`, `mut_state` [6].

### Estados del Filósofo [6]

Cada filósofo puede estar en uno de los siguientes estados:

*   `OFF`: Estado inicial, antes de que el simulador comience.
*   `THINKING`: El filósofo está pensando.
*   `EATING`: El filósofo está comiendo (ha tomado ambos tenedores).
*   `SLEEPING`: El filósofo está durmiendo (después de comer).
*   `DIE`: El filósofo ha muerto por inanición.
*   `FULL`: El filósofo ha comido el número de veces requerido (si `nb_meals` es definido).

### Ciclo de Vida del Filósofo

El `main` de cada hilo filósofo ejecuta un bucle continuo (hasta que se detenga el simulador o el filósofo muera):

1.  **Pensar**: El filósofo entra en el estado `THINKING` y espera un tiempo (`time_to_think` implícito).
2.  **Intentar Comer**: El filósofo intenta tomar sus dos tenedores adyacentes.
3.  **Comer**: Si consigue ambos tenedores, entra en el estado `EATING`, actualiza `last_eat`, incrementa `meals`, y espera `time_to_eat`.
4.  **Dormir**: Después de comer, deja los tenedores, entra en el estado `SLEEPING` y espera `time_to_sleep`.

### Estrategia para Evitar Deadlocks

La implementación evita deadlocks mediante una de las siguientes estrategias comunes:

*   **Ordenación de Recursos**: Establece un orden global para tomar los tenedores. Por ejemplo, todos los filósofos intentan tomar el tenedor con el índice más bajo primero, y luego el tenedor con el índice más alto. Esto rompe la condición de espera circular.
    *   **Ejemplo en `ft_get_forks` [7]**: Se compara `philo->fork_l` y `philo->fork_r` para asegurar un orden consistente (`first = min(fork_l, fork_r)`, `second = max(fork_l, fork_r)`).
*   **Filósofo "Diestro" / "Zurdo"**: Una variante de la ordenación. Un número impar de filósofos toman el tenedor izquierdo primero, y los pares toman el derecho primero (o viceversa).
*   **Un Filósofo a la Vez**: Permitir que solo N-1 filósofos (todos menos uno) tomen su primer tenedor a la vez.

### Manejo del Tiempo y Monitoreo

*   **Timestamps**: Todas las acciones importantes (tomar tenedor, comer, dormir, pensar, morir) se loguean con un timestamp relativo al inicio de la simulación.
*   **Monitores**: Un hilo(s) monitor(es) se ejecuta en segundo plano.
    *   **Monitor de Muerte**: Periódicamente, revisa el `last_eat` de cada filósofo. Si `current_time - last_eat > time_to_die`, el filósofo se marca como `DIE` y el simulador se detiene.
    *   **Monitor de Comidas (opcional)**: Si se especifica `nb_meals`, este monitor comprueba si todos los filósofos han comido el número requerido de veces, deteniendo el simulador si es así.

---

## 🛠️ Compilación y Ejecución

El proyecto se compila y gestiona con un `Makefile` estándar de 42.

1.  **Navega al directorio del proyecto**:
    ```bash
    cd <directorio_del_proyecto_philosophers> # Ej: cd philo
    ```
2.  **Compilar el ejecutable**:
    ```bash
    make
    # O para una reconstrucción limpia (recomendado):
    make re
    ```
    El ejecutable generado se llamará `philo` (o similar, definido en el `Makefile`).

3.  **Ejecutar el programa**:
    El programa toma los siguientes argumentos en la línea de comandos:

    ```bash
    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
    ```
    *   `<number_of_philosophers>`: Número de filósofos y, por ende, de tenedores (ej. 5).
    *   `<time_to_die>`: Tiempo en milisegundos que un filósofo puede pasar sin comer antes de morir (ej. 800).
    *   `<time_to_eat>`: Tiempo en milisegundos que un filósofo tarda en comer (ej. 200).
    *   `<time_to_sleep>`: Tiempo en milisegundos que un filósofo tarda en dormir (ej. 200).
    *   `[number_of_times_each_philosopher_must_eat]` (Opcional): Si se especifica, el simulador terminará cuando cada filósofo haya comido este número de veces.

*   **Ejemplo de Ejecución**:
    ```bash
    ./philo 5 800 200 200
    # O con número de comidas:
    ./philo 4 410 200 200 7
    ```

---

## 🧪 Testing y Validación

La validación del proyecto "Filósofos" es compleja, ya que requiere verificar no solo que el programa termina, sino que lo hace correctamente y sin violar las reglas de concurrencia.

*   **Sin Deadlocks**: El programa nunca debe quedarse bloqueado indefinidamente. Todos los filósofos deben poder avanzar en sus ciclos, aunque no coman al mismo tiempo.
*   **Sin Starvation**: En una ejecución prolongada, todos los filósofos deben comer un número razonable de veces. Ninguno debe morir por inanición si la configuración lo permite (ej. `time_to_die` es suficientemente grande).
*   **Condiciones de Muerte**: Si un filósofo no come a tiempo (`time_to_die`), el programa debe anunciar su muerte y terminar.
*   **Condición de Comidas Completadas**: Si se especifica `number_of_times_each_philosopher_must_eat`, el programa debe terminar cuando todos los filósofos hayan alcanzado ese objetivo.
*   **Output Consistente**: Los mensajes de log deben ser claros, consistentes y con los timestamps correctos.
*   **Ausencia de Fugas de Memoria**: Uso de `Valgrind` para verificar que no hay fugas de memoria, acceso inválido a memoria o condiciones de carrera en el uso de mutexes.

    ```bash
    valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./philo 5 800 200 200
    ```

---

## ✍️ Autor

*   **Nombre**: Juan Jesús Márquez
*   **Perfil GitHub**: https://github.com/elWare
*   **42 Login**: https://profile-v3.intra.42.fr/users/jumarque

