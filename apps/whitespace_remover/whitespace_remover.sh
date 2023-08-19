#!/bin/bash

# Definir la ruta de búsqueda (dos carpetas atrás desde la ubicación actual)
search_path="../.."

# Buscar archivos .cpp y .h en la ruta especificada
find "$search_path" -type f \( -name '*.cpp' -o -name '*.h' \) | while read -r file; do
  # Eliminar los espacios en blanco al final de las líneas usando sed
  sed -i 's/[[:blank:]]\+$//' "$file"
done
