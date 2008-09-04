#ifndef PAGINA_HPP_
#define PAGINA_HPP_

template<typename tipoDado>
class Pagina
{
	public:
		typedef std::vector< Pagina<tipoDado> > Paginacao;

		Pagina( )
		{
			this->modificado = false;
		}

		/*const */tipoDado
		getDado( )
		{
			return this->dado;
		}

		/*const */bool
		getModificado( )
		{
			return this->modificado;
		}

		void
		setDado( /*const */tipoDado _dado )
		{
			this->dado = _dado;
		}

		void
		setModificado( bool _modificado )
		{
			this->modificado = _modificado;
		}

		void
		operator =( tipoDado _dado )
		{
			this->setDado( _dado );
		}

		virtual
		~Pagina( )
		{

		}

	protected:

	private:
		tipoDado
		dado;

		bool
		modificado;
};

#endif /* PAGINA_HPP_ */
