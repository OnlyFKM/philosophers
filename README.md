# Philosophers

Este proyecto simula el clásico problema de los filósofos, donde un grupo de filósofos se sienta alrededor de una mesa redonda con un tazón de espaguetis en el centro. Los filósofos pueden realizar tres acciones: comer, pensar y dormir, con restricciones específicas sobre cuándo pueden realizar cada una de estas actividades.

## Descripción del problema

- Uno o más filósofos se sientan en una mesa redonda.
- Los filósofos solo pueden comer, pensar o dormir.
- Durante la comida, no pueden pensar ni dormir; durante el pensamiento, no pueden dormir ni comer; y mientras duermen, no pueden comer ni pensar.
- Hay tenedores en la mesa, uno por cada filósofo.
- Los filósofos deben tomar el tenedor de la derecha y el de la izquierda para comer.
- Después de comer, dejan los tenedores en la mesa y comienzan a dormir. Después de despertar, vuelven a pensar.
- La simulación termina cuando un filósofo muere de inanición.
- Todos los filósofos necesitan comer y no deben morir de hambre.
- Los filósofos no hablan entre ellos y no saben si otro filósofo va a morir.

## Reglas de implementación

- Se deben crear dos programas: uno para la parte obligatoria y otro para la parte bonus (opcional).
- Las variables globales están prohibidas.
- Los programas deben aceptar los siguientes argumentos:
  - **number_of_philosophers**: número de filósofos y tenedores.
  - **time_to_die**: tiempo en milisegundos para que un filósofo muera si no comienza a comer.
  - **time_to_eat**: tiempo en milisegundos que un filósofo tiene para comer.
  - **time_to_sleep**: tiempo en milisegundos que un filósofo tiene para dormir.
  - **[number_of_times_each_philosopher_must_eat]**: argumento opcional para detener la simulación cuando todos los filósofos han comido cierto número de veces.
- Cada filósofo tiene asignado un número del 1 al **number_of_philosophers**.
- Los logs del programa deben seguir el formato especificado.

## Ejecución del programa

Para ejecutar el programa obligatorio:

    ./philosophers number_philosophers time_die time_eat time_sleep [number_times_must_eat]
