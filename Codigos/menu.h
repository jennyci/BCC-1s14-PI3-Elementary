//inicializando o menu

void carregarTela()
{
	Display = al_create_display(Largura_Tela, Altura_Tela);

	if(!Display)
	{
	    fprintf(stderr, "Falha ao criar a janela\n");
	}

	fundoDisplay = al_load_bitmap(Imagens/Elementary.png);

	if(!fundoDisplay)
	{
		fprintf(stderr, "Falha ao criar o Fundo\n");
	}

	al_set_window_title(Display,"Elementary");

    iniciarMenu = al_create_bitmap(250,60)

    if(!iniciarMenu)
    {
    	fprintf(stderr, "Falha ao criar bitmap\n");
    	al_destroy_display(Display);
    }

    sairMenu = al_create_bitmap(130,55);

    if(!sairMenu)
    {
        fprintf(stderr, "Falha ao criar o botão de saída\n");
        al_destroy_display(Display);
    }

    

}
