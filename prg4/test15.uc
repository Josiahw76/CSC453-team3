main()
{ int j, k;
  k = 22;
  for (j = 0; j < 100; j += 1) {
     k = k + j;
     if (k > 120) 
        j = 100;
     else
        k = k + 10;
  }
  return k;
}
