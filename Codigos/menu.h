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

    if(!iniciarFogo)
    {  
        fogoMenu = al_load_bitmap(Imagens//*Primeira imagem do tipo Fogo*/);
        fprintf(stderr,"Falha ao carregar Fogo1\n");
    }
    else
    {
        fogoMenu = al_load_bitmap(Imagens//*Segunda imagem do tipo Fogo*/);
        fprintf(stderr, "Falha ao carregar Fogo2\n");
    }

    if(!iniciarAgua)
    {
        aguaMenu = al_load_bitmap(Imagens//*Primeira imagem do tipo Agua*/);
        fprintf(stderr, "Falha ao carregar Agua1\n");
    }
    else
    {
        aguaMenu = al_load_bitmap(Imagens//*Segunda imagem do tipo Agua*/)
        fprintf(stderr, "Falha ao carregar Agua2\n");
    }

    if(!iniciarPlanta)
    {
        plantaMenu = al_load_bitmap(Imagens//*Primeira imagem de Planta*/);
        fprintf(stderr, "Falha ao carregar Planta1\n");
    }

    else
        {
            plantaMenu = al_load_bitmap(Imagens//*Segunda imagem de Planta*/);
            fprintf(stderr, "Falha ao carregar Planta2\n");
        }

    al_set_target_bitmap(al_get_backbuffer(Display));
    al_draw_bitmap(fundoDisplay,0,0,0);
    al_draw_bitmap(iniciarMenu,300 ,170 , 0);
    al_draw_bitmap(continuarMenu, 290,250,0);
    al_draw_bitmap(sairMenu,360,320,0);
    // Atualiza a tela
    al_flip_display();
   

}
