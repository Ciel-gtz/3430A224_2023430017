<div align="center">
<h1>Algoritmo de Prim</h1>
</div>

se utiliza como base el algoritmo de dijkstra del laboratorio 6

// https://cp-algorithms.com/graph/mst_prim.html como ejemplo de algoritmo de prim


- Se agregó la función actualizar_pesos_prim() para manejar los pesos en Prim.
- Se agregó la función imprimir_grafo() para generar visualizaciones con Graphviz.
- Se modificó elegir_vertice() para seleccionar vértices por peso directo, no acumulado.
- Se reescribió aplicar_prim() reemplazando el flujo de Dijkstra por el de Prim.
- Se actualizó leer_datos_matriz() para copiar valores simétricos automáticamente.
- Se adaptó main() para inicializar matrizMST, imprimir V[], y mostrar grafos.
- Se eliminaron funciones de Dijkstra (aplicar_dijkstra, actualizar_pesos_dijkstra).

