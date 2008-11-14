#ifndef PAGINA_HPP_
#define PAGINA_HPP_

#include <queue>
#include <vector>

template<typename T>
class Pagina
{
	public:
		typedef std::vector< Pagina<T> > Paginacao;

		Pagina( )
		{
			this->modificado = false;
		}

		T
		getDado( )
		{
			return this->dado;
		}

		bool
		getModificado( )
		{
			return this->modificado;
		}

		void
		setDado( T _dado )
		{
			this->dado = _dado;
		}

		void
		setModificado( bool _modificado )
		{
			this->modificado = _modificado;
		}

		void
		operator =( T _dado )
		{
			this->setDado( _dado );
		}

		virtual
		~Pagina( )
		{

		}

	protected:

	private:
		T
		dado;

		bool
		modificado;
};

#endif /* PAGINA_HPP_ */
