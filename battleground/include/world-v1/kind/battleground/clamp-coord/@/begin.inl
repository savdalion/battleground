// Выполнение begin-ядра на C++.
// @require include "_.h"


// ПОЛЕ БИТВЫ
// @todo optimize Когда элементов мало, отдавать алгоритм для CPU.
enqueueEventKernelCL< BATTLEGROUND_COUNT >( "battleground/clamp-coord/@/begin" );
