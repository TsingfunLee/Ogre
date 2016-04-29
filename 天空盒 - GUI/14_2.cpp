//#include "stdafx.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

#include <ogre/Ogre.h>
#include <ois/OIS.h>
#include <ogre/SdkTrays.h>
#include "ogre/OgreConfigFile.h"

using namespace std;

using namespace Ogre;

#ifdef _DEBUG
#define PLUGINS_CFG "plugins_d.cfg"
#else
#define PLUGINS_CFG "plugins.cfg"
#endif


class Tutorial9: public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, 
	OgreBites::SdkTrayListener {
private:
	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneNode* cameraNo;

	OgreBites::SdkTrayManager* mTrayMgr;

	OIS::InputManager *mInputManager;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;

	bool desligar;

	//Widgets
	OgreBites::Button *button;
	OgreBites::TextBox *textBox;
	OgreBites::SelectMenu *selectMenu;
	OgreBites::Label *label;
	OgreBites::Separator *separator;
	OgreBites::Slider *slider;
	OgreBites::ParamsPanel *paramsPanel;
	OgreBites::CheckBox *checkbox;
	OgreBites::ProgressBar *progressBar;

	void criarInterfaceGrafica(){

		Ogre::StringVector paramsPanelItems;
		paramsPanelItems.push_back("X");
		paramsPanelItems.push_back("Y");
		paramsPanelItems.push_back("Z");
		
		textBox		= mTrayMgr->createTextBox( OgreBites::TL_NONE, "textBox", "", 200, 100 );
		
		selectMenu	= mTrayMgr->createThickSelectMenu( OgreBites::TL_TOP, "selectMenu", "", 200, 200 );
		separator	= mTrayMgr->createSeparator( OgreBites::TL_TOPRIGHT, "separator", 200 );
		paramsPanel	= mTrayMgr->createParamsPanel(OgreBites::TL_LEFT, "paramsPanel",  200, paramsPanelItems );
		label		= mTrayMgr->createLabel( OgreBites::TL_CENTER, "label", "", 500 );
		
		mRoot->renderOneFrame();

		slider		= mTrayMgr->createThickSlider( OgreBites::TL_RIGHT, "slider", "", 200, 80, 1, 32, 32);
		checkbox	= mTrayMgr->createCheckBox(OgreBites::TL_BOTTOMLEFT, "checkbox",  "", 200 );		
		progressBar	= mTrayMgr->createProgressBar( OgreBites::TL_BOTTOM, "progressBar", "", 200, 100);
		button		= mTrayMgr->createButton( OgreBites::TL_BOTTOMRIGHT, "button", "", 200 );

		label->setCaption( "Label" );
		button->setCaption( "Button" );
		textBox->setCaption( "Texto" );
		textBox->getOverlayElement()->setTop(0);
		textBox->getOverlayElement()->setLeft(0);
		
		selectMenu->setCaption( "Selecione:" );
		selectMenu->addItem( "Otion 1" );
		selectMenu->addItem( "Otion 2" );
		selectMenu->addItem( "Otion 3" );

		slider->setCaption( "Slider" );

		paramsPanel->setParamValue( 0, "0" );
		paramsPanel->setParamValue( 1, "1" );
		paramsPanel->setParamValue( 2, "2" );

		checkbox->setCaption( "CheckBox" );
		checkbox->setChecked( true );

		progressBar->setCaption( "Progess" );
		progressBar->setProgress( 0.8f );

		mRoot->renderOneFrame();
		
	}

	bool carregarConfiguracaoOgre(){
		bool usuarioConfirmou = true;
		// mRoot->restoreConfig() Verifica se ja existe configura玢o no ogre.cfg
		// se existir retorna true e entra no if
		// sen鉶 cai no OU e mostra a tela para escolher configura玢o
		if(mRoot->restoreConfig() || mRoot->showConfigDialog()){
			// O primeiro par鈓etro diz ao Ogre que ele pode criar uma janela para renderiza玢o
			// O segundo par鈓etro ?o titulo da Janela
			mWindow = mRoot->initialise(true, "Ponto V - Tutorial 9");
		}else{
			// Caso o usu醨io aperte cancel na tela do ogre feche o programa
			usuarioConfirmou = false;
		}

		return usuarioConfirmou;
	}

	void inicializarCamera(){
		cameraNo = mSceneMgr->getRootSceneNode()->createChildSceneNode( "cameraNode" );

		// Cria a camera
		mCamera = mSceneMgr->createCamera("Camera");
 
		// ViewPort ?o que faz a cena ser renderizado pela camera
		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		// Cor de fundo do ViewPort
		vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
 
		// Muda o aspecto(width, height) da camera para se adequar ao ViewPort
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		// Posiciona a Camera
		mCamera->setPosition(Ogre::Vector3(0, 0, 0));
		// Manda a camera olhar para um ponto
		mCamera->lookAt( 0, 0, 0 );
		// Distancia m韓ima para que o objeto deve estar da camera para ser renderziado
		mCamera->setNearClipDistance(1);
		// Distancia m醲ima para que o objeto deve estar da camera para ser renderziado
		mCamera->setFarClipDistance(1000);

		cameraNo->attachObject( mCamera );
		cameraNo->setPosition( 0, 0, -30 );
		cameraNo->lookAt( Ogre::Vector3( 0, 0, 0 ), Ogre::Node::TS_WORLD );
	}

	void inicializarRecursos(){
		// Carregando as pastas dos resources

		ConfigFile cf;
		cf.load("resources_d.cfg");
		// Go through all sections & settings in the file
		ConfigFile::SectionIterator seci = cf.getSectionIterator();

		String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			ConfigFile::SettingsMultiMap *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;

				ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);

			}
		}
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void inicializarOIS(){
		
		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
 
		// Cria os par鈓etros para inicializar o OIS
		mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
		// Cria o OIS
		mInputManager = OIS::InputManager::createInputSystem( pl );
 
		// Inicializa vari醰el respons醰el pelo teclado
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
		// Inicializa vari醰el respons醰el pelo mouse
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
 
		// P鮡 como Event Callback a atual inst鈔cia dessa classe
		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);
	}

	void inicializarEventosJanela(){
		// Ajusta as dimens鮡s do OIS para o MOUSE.
		windowResized(mWindow);

		// Registra essa inst鈔cia apra ler os eventos da janela
		Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

		mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
	}
public:

	Tutorial9(void){
		mTrayMgr = 0;

		srand( (unsigned)time( NULL ) );

		desligar = false;

	}

	~Tutorial9(void){

		mTrayMgr->destroyAllWidgets();

		if (mTrayMgr) delete mTrayMgr;

		// Remove essa inst鈔cia dos listeners
		Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

		// Fecha a Janela
		windowClosed(mWindow);

		delete mRoot;
	}

	bool frameStarted(const Ogre::FrameEvent& evt){
		// Caputra entrada de teclado
		mKeyboard->capture();
		// Caputra entrada de Mouse
		mMouse->capture();

		return true;
	}

	// M閠odo da Interface FrameListener, ?chamado no Loop Principal
	bool frameRenderingQueued(const Ogre::FrameEvent& evt){
		if (desligar) return false;

		mTrayMgr->frameRenderingQueued(evt);

		// Parar o programa caso a janela seja fechada
		if(mWindow->isClosed())
			return false;

		return true;
	}

	bool inicializarOgre(){ 

		// Construi o Root do Ogre
		mRoot = new Ogre::Root(PLUGINS_CFG);
 
		// Carrega Configura玢o do Ogre
		if( !carregarConfiguracaoOgre() ) return false;

		// Escolhendo o gerenciador de cenas
		mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
		
		// Carrega a c鈓era
		inicializarCamera();

		// Coloca o n鷐ero padr鉶 de MipMaps
		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Carrega Todos resoures
		inicializarRecursos();
		
		// Carrega o OIS
		inicializarOIS();

		// Carrega os Eventos da Janela
		inicializarEventosJanela();

		//Adiciona essa inst鈔cia da classe como frame Listener
		mRoot->addFrameListener(this);

		return true;
	}

	bool criarCena(){
		criarInterfaceGrafica();

		// Cria Luz ambiente
		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
		// Cria uma Luz
		Ogre::Light* l = mSceneMgr->createLight("Luz");
		l->setPosition(0, 0, 100);

		// Come鏰 a renderizar
		mRoot->startRendering();

		return false;
	}

	//响应按钮事件
	void buttonHit(OgreBites::Button* bt) {
		Ogre::String message( "botao name = " );
		message.append( bt->getName() );
		message.append( " caption = " );
		message.append( bt->getCaption() );

		label->setCaption(message);
	}
	//响应选择框事件
	void itemSelected(OgreBites::SelectMenu* menu) {
		Ogre::String message( "item selcted = " );
		message.append( menu->getSelectedItem() );
		message.append( " menu name = ");
		message.append( menu->getName() );

		label->setCaption(message);
	}

	//响应标签事件
	void labelHit(OgreBites::Label* lb) {
		Ogre::String message( "label name = " );
		message.append( lb->getName() );

		label->setCaption(message);
	}

	//响应滑块事件
	void sliderMoved(OgreBites::Slider* sl) {
		Ogre::String message( "slider name = " );
		message.append( sl->getName() );
		message.append( " caption = " );
		message.append( sl->getCaption() );
		message.append( " value = " );
		message.append( Ogre::StringConverter::toString( sl->getValue() ) );

		label->setCaption(message);
	}

	//响应检查框事件
	void checkBoxToggled(OgreBites::CheckBox* box) {
		Ogre::String message( "check name = " );
		message.append( box->getName() );
		message.append( " checked = " );
		message.append( Ogre::StringConverter::toString( box->isChecked() ) );

		label->setCaption(message);
	}

protected:

	// M閠odo da Interface KeyListener ?chamado quando uma tecla ?apertada no teclado
	bool keyPressed( const OIS::KeyEvent &arg ){
		switch (arg.key){
		case OIS::KC_ESCAPE:
			desligar = true;
			break;
		}
		return true;
	}

	// M閠odo da Interface KeyListener ?chamado quando uma tecla ?solta no teclado
	bool keyReleased( const OIS::KeyEvent &arg ){

		return true;
	}


	// M閠odo da Interface MouseListener ?chamado quando o mouse ?movido
	bool mouseMoved( const OIS::MouseEvent &arg ){
		if (mTrayMgr->injectMouseMove(arg)) return true;

		return true;
	}

	// M閠odo da Interface MouseListener ?chamado algum bot鉶 do mouse ?apertado
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
		if (mTrayMgr->injectMouseDown(arg, id)) return true;

		return true;
	}

	// M閠odo da Interface MouseListener ?chamado algum bot鉶 do mouse ?solto
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
		if (mTrayMgr->injectMouseUp(arg, id)) return true;

		return true;
	}

	//Ajustando a 醨ea a qual o mouse pode movimentar
	void windowResized(Ogre::RenderWindow* rw){
		unsigned int width, height, depth;
		int left, top;
		rw->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = mMouse->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	//Unattach OIS before window shutdown (very important under Linux)
	void windowClosed(Ogre::RenderWindow* rw){
		//Only close for window that created OIS (the main window in these demos)
		if( rw == mWindow )
		{
			if( mInputManager )
			{
				mInputManager->destroyInputObject( mMouse );
				mInputManager->destroyInputObject( mKeyboard );

				OIS::InputManager::destroyInputSystem(mInputManager);
				mInputManager = 0;
			}
		}
	}

};

int main()
{
	Tutorial9 application;
	try {
		if( application.inicializarOgre() ){
			application.criarCena();
		}
	} catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;

	}

	return 0;
}