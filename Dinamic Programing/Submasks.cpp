/*
Todas las submascaras de una mascara con los bits activos
*/

//inicio
for (int s=mask; s; s=(s-1)&mask)
{
		//you can use s....
        cout << s << endl;
		//if(s==0) break; para no procesar el 0
}
//fin

/*
Tods las submascaras de una mascara con los bits no activos
*/
//inicio
int k = log2(m);
for(int s = (1<<k)-1; (s &= ~m) >= 0; s--){
	//You can use the s ...
	cout << s << endl;
}
