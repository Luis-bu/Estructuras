#ifndef __POLINOMIO__HXX__
#define __POLINOMIO__HXX__

// -------------------------------------------------------------------------
template < class S > 
Polinomio<S>::
Polinomio( )
{
}

// -------------------------------------------------------------------------
template < class S > 
Polinomio<S>::
~Polinomio( )
{
}

// -------------------------------------------------------------------------
template < class S > 
void Polinomio<S>::FijarCoeficiente( unsigned int grado, const S& coeficiente )
{
  if( grado >= this->size( ) )
    this->resize( grado + 1, S( 0 ) );
  ( *this )[ grado ] = coeficiente;
}

// -------------------------------------------------------------------------
// SUMA
template < class S > 
Polinomio<S> Polinomio<S>::operator+( const Polinomio< S >& der ) const
{
  Polinomio<S> resultado;

  //Se obtiene el tamaño de los polinomios
  unsigned int tamIzq = (unsigned int)this->size();
  unsigned int tamDer = (unsigned int)der.size();

  //El resultado es el que debe tener el tamaño más grande entre los 2
  unsigned int tamRes = (tamIzq > tamDer) ? tamIzq : tamDer;

  // si los dos polinomios están vacíos, devolvemos uno vacio
  if (tamRes == 0)
    return resultado;

  // redimensionamos el polinomio resultado con ceros
  resultado.resize(tamRes, S(0));

  for (unsigned int i = 0; i < tamRes; ++i)
  {
    // si el grado existe en el polinomio izq y der lo tomamos, si no se pone 0
    S ai = (i < tamIzq) ? (*this)[i] : S(0);
    S bi = (i < tamDer) ? der[i]     : S(0);
    // la suma de los coeficientes la guardamos en resultado
    resultado[i] = ai + bi;
  }
  // devuelvo el polinomio resultado (por valor)
  return resultado; 
}

// -------------------------------------------------------------------------
// PRODUCTO
template < class S > 
Polinomio<S> Polinomio<S>::operator*( const Polinomio< S >& der ) const
{
  Polinomio<S> resultado;

  unsigned int tamIzq = (unsigned int)this->size();
  unsigned int tamDer = (unsigned int)der.size();

  if (tamIzq == 0 || tamDer == 0)
    return resultado; // vacío

  unsigned int tamRes = tamIzq + tamDer - 1;
  resultado.resize(tamRes, S(0));

  for (unsigned int i = 0; i < tamIzq; ++i)
  {
    for (unsigned int j = 0; j < tamDer; ++j)
    {
      resultado[i + j] += (*this)[i] * der[j];
    }
  }

  return resultado; // devolver por valor
}

// -------------------------------------------------------------------------
// EVALUACIÓN
template < class S > 
S Polinomio<S>::operator()( const S& x ) const
{
  S resultado = S( 0 );
  int n = (int)this->size();

  for (int i = n - 1; i >= 0; --i)
  {
    resultado = resultado * x + (*this)[ (unsigned int)i ];
  }

  return resultado;
}

#endif // __POLINOMIO__HXX__

// eof - Polinomio.hxx
