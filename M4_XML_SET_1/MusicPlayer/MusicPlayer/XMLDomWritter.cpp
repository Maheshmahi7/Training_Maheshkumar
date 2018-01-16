#include "XMLDomWritter.h"

XMLDomWritter::XMLDomWritter(DOMDocument* doc){
	xmlDoc = doc;
}
XMLDomWritter::~XMLDomWritter(){}
void XMLDomWritter::addElementToFile(){

	DOMImplementation    *pImplement = NULL;
	DOMLSSerializer      *pSerializer = NULL;
	XMLFormatTarget      *pTarget = NULL;

	pImplement = DOMImplementationRegistry::getDOMImplementation(L"LS");

	pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();


	DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
	pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);


	pTarget = new LocalFileFormatTarget(XMLString::transcode("C:\\Users\\jayaraj-1\\Documents\\Visual Studio 2013\\Projects\\MusicPlayerApplication\\MusicPlayerApplication\\MusicPlayerData.xml"));
	// Write the serialized output to the target.
	DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
	pDomLsOutput->setByteStream(pTarget);

	pSerializer->write(xmlDoc, pDomLsOutput);

}

void XMLDomWritter::addElementSong(){
	wstring song;
	const wchar_t* wSong;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));

	XMLCh* temp = XMLString::transcode("songs");
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));

	p_DataElement = xmlDoc->createElement(L"song");

	cout << "Enter Song ID" << endl;
	wcin >> song;
	wSong = song.c_str();

	p_DataElement->setAttribute(L"ID", wSong);

	p_RootElement->appendChild(p_DataElement);


	data = xmlDoc->createElement(L"song_name");

	cout << "Enter the song name that you want to add" << endl;
	wcin >> song;

	wSong = song.c_str();

	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);


	data = xmlDoc->createElement(L"duration");
	cout << "Enter the song duration" << endl;
	wcin >> song;
	wSong = song.c_str();

	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"song_album");
	cout << "Enter the album name" << endl;
	wcin >> song;
	wSong = song.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"song_artists");
	cout << "Enter the number artists contributed" << endl;

	cin >> index;

	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"song_artist");
		cout << "Enter the artist name" << endl;
		wcin >> song;
		wSong = song.c_str();
	
		textNode = xmlDoc->createTextNode(wSong);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	//addElementToFile(xmlDoc, XMLString::transcode("C:\\Users\\jayaraj-1\\Documents\\Visual Studio 2013\\Projects\\MusicPlayerApplication\\MusicPlayerApplication\\MusicPlayerData.xml"));
	
}

void XMLDomWritter::addElementArtist(){
	int id = 216;
	wstring artist;
	const wchar_t* wArtist;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));

	XMLCh* temp = XMLString::transcode("artists");
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));

	p_DataElement = xmlDoc->createElement(L"artist");

	cout << "Enter Artist ID" << endl;
	wcin >> artist;
	wArtist = artist.c_str();

	p_DataElement->setAttribute(L"ID", wArtist);

	p_RootElement->appendChild(p_DataElement);

	data = xmlDoc->createElement(L"artist_name");

	cout << "Enter the artist name that you want to add" << endl;
	wcin >> artist;

	wArtist = artist.c_str();

	textNode = xmlDoc->createTextNode(wArtist);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"artist_albums");
	cout << "Enter the number of albums artists contributed" << endl;
	cin >> index;
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"artist_album");
		cout << "Enter the album name" << endl;
		wcin >> artist;
		wArtist = artist.c_str();

		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"artist_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"artist_song");
		cout << "Enter the song name;" << endl;
		wcin >> artist;
		wArtist = artist.c_str();

		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	
	//addElementToFile(xmlDoc, XMLString::transcode("C:\\Users\\jayaraj-1\\Documents\\Visual Studio 2013\\Projects\\MusicPlayerApplication\\MusicPlayerApplication\\MusicPlayerData.xml"));
}

void XMLDomWritter::addElementAlbum(){
	int id = 316;
	wstring album;
	const wchar_t* wAlbum;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));

	XMLCh* temp = XMLString::transcode("albums");
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));

	p_DataElement = xmlDoc->createElement(L"album");

	cout << "Enter Album ID" << endl;
	wcin >> album;
	wAlbum = album.c_str();

	p_DataElement->setAttribute(L"ID", wAlbum);

	p_RootElement->appendChild(p_DataElement);

	data = xmlDoc->createElement(L"album_name");

	cout << "Enter the album name that you want to add" << endl;
	wcin >> album;

	wAlbum = album.c_str();

	textNode = xmlDoc->createTextNode(wAlbum);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"album_artists");
	cout << "Enter the number of artist contributed" << endl;
	cin >> index;
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"album_artist");
		cout << "Enter the artist name" << endl;
		wcin >> album;
		wAlbum = album.c_str();

		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"album_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"album_song");
		cout << "Enter the song name;" << endl;
		wcin >> album;
		wAlbum = album.c_str();

		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	//addElementToFile(xmlDoc, XMLString::transcode("C:\\Users\\jayaraj-1\\Documents\\Visual Studio 2013\\Projects\\MusicPlayerApplication\\MusicPlayerApplication\\MusicPlayerData.xml"));
}

void XMLDomWritter::createPlaylist(){
	int id = 415;
	wstring playlist;
	const wchar_t* wPlaylist;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));

	XMLCh* temp = XMLString::transcode("playlists");
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));


	p_DataElement = xmlDoc->createElement(L"playlist");

	cout << "Enter Playlist ID" << endl;
	wcin >> playlist;
	wPlaylist = playlist.c_str();

	p_DataElement->setAttribute(L"ID", wPlaylist);

	p_RootElement->appendChild(p_DataElement);

	data = xmlDoc->createElement(L"playlist_name");

	cout << "Enter the playlist name that you want to add" << endl;
	wcin >> playlist;

	wPlaylist = playlist.c_str();

	textNode = xmlDoc->createTextNode(wPlaylist);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"playlist_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"playlist_song");
		cout << "Enter the song name;" << endl;
		wcin >> playlist;
		wPlaylist = playlist.c_str();

		textNode = xmlDoc->createTextNode(wPlaylist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	//addElementToFile(xmlDoc, XMLString::transcode("C:\\Users\\jayaraj-1\\Documents\\Visual Studio 2013\\Projects\\MusicPlayerApplication\\MusicPlayerApplication\\MusicPlayerData.xml"));
}