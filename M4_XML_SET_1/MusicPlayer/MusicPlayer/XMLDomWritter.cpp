#include "XMLDomWritter.h"

/*parameterized constructor to assign the readed file to local instance*/
XMLDomWritter::XMLDomWritter(DOMDocument* doc){
	xmlDoc = doc;
}
XMLDomWritter::~XMLDomWritter(){
}

/*Method to write the xml from memory to local file*/
void XMLDomWritter::addElementToFile(){

	DOMImplementation    *pImplement = NULL;
	DOMLSSerializer      *pSerializer = NULL;
	XMLFormatTarget      *pTarget = NULL;

	pImplement = DOMImplementationRegistry::getDOMImplementation(L"LS");

	pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();


	DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
	pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);


	pTarget = new LocalFileFormatTarget("./MusicPlayerData.xml");
	DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
	pDomLsOutput->setByteStream(pTarget);

	pSerializer->write(xmlDoc, pDomLsOutput);
}

/*Mehtod to add songs element to the xml file*/
DOMDocument* XMLDomWritter::addElementSong(){
	wstring song;
	string name,duration,album,artist;
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
	cin.get(); 
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wSong = wName.c_str();

	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);


	data = xmlDoc->createElement(L"duration");
	cout << "Enter the song duration" << endl;
	cin.get(); 
	getline(cin, duration);
	wstring wDuration(duration.begin(), duration.end());
	wSong = wDuration.c_str();

	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"song_album");
	cout << "Enter the album name" << endl;
	cin.get(); 
	getline(cin, album);
	album = getChildByName("album", "album_name", album.c_str());
	wstring wAlbum(album.begin(), album.end());
	wSong = wAlbum.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"song_artists");
	cout << "Enter the number artists contributed" << endl;

	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}

	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"song_artist");
		cout << "Enter the artist name" << endl;
		cin.get(); 
		getline(cin, artist);
		artist = getChildByName("artist", "artist_name", artist.c_str());
		wstring wArtist(artist.begin(), artist.end());
		wSong = wArtist.c_str();
	
		textNode = xmlDoc->createTextNode(wSong);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	return xmlDoc;

}

/*Method to add the artist element to the xml file*/
DOMDocument* XMLDomWritter::addElementArtist(){
	int id = 216;
	wstring artist;
	string name, album, song;
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
	cin.get(); 
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wArtist = wName.c_str();
	
	textNode = xmlDoc->createTextNode(wArtist);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"artist_albums");
	cout << "Enter the number of albums artists contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"artist_album");
		cout << "Enter the album name" << endl;
		cin.get(); 
		getline(cin, album);
		album = getChildByName("album", "album_name", album.c_str());
		wstring wAlbum(album.begin(), album.end());
		wArtist = wAlbum.c_str();

		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"artist_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"artist_song");
		cout << "Enter the song name;" << endl;
		cin.get(); 
		getline(cin, song);
		song = getChildByName("song", "song_name", song.c_str());
		wstring wSong(song.begin(), song.end());
		wArtist = wSong.c_str();

		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	return xmlDoc;
}

/*Method to add the album element to the xml file*/
DOMDocument* XMLDomWritter::addElementAlbum(){
	int id = 316;
	string name, song, artist;
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
	wstring album;
	wcin >> album;
	wAlbum = album.c_str();

	p_DataElement->setAttribute(L"ID", wAlbum);

	p_RootElement->appendChild(p_DataElement);

	data = xmlDoc->createElement(L"album_name");

	cout << "Enter the album name that you want to add" << endl;
	cin.get(); 
	getline(cin, name);
	wstring wName(name.begin(),name.end());
	wAlbum = wName.c_str();

	textNode = xmlDoc->createTextNode(wAlbum);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"album_artists");
	cout << "Enter the number of artist contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"album_artist");
		cout << "Enter the artist name" << endl;
		cin.get(); 
		getline(cin, artist);
		artist = getChildByName("artist", "artist_name", artist.c_str());
		wstring wArtist(artist.begin(), artist.end());
		wAlbum = wArtist.c_str();

		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"album_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"album_song");
		cout << "Enter the song name;" << endl;
		cin.get(); 
		getline(cin, song);
		song = getChildByName("song", "song_name", song.c_str());
		wstring wSong(song.begin(), song.end());
		wAlbum = wSong.c_str();

		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	return xmlDoc;
}

/*Method to add the playlist element to the xml file*/
DOMDocument* XMLDomWritter::createPlaylist(){
	int id = 415;
	string name,songs;
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
	wstring playlist;
	wcin >> playlist;
	wPlaylist = playlist.c_str();

	p_DataElement->setAttribute(L"ID", wPlaylist);

	p_RootElement->appendChild(p_DataElement);

	data = xmlDoc->createElement(L"playlist_name");

	cout << "Enter the playlist name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	//wcin.get();
	wPlaylist = wName.c_str();

	textNode = xmlDoc->createTextNode(wPlaylist);
	data->appendChild(textNode);

	p_DataElement->appendChild(data);

	data = xmlDoc->createElement(L"playlist_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"playlist_song");
		cout << "Enter the song name;" << endl;
		
		cin >> songs;

		songs=getChildByName("song", "song_name", songs.c_str());

		wstring wSong(songs.begin(), songs.end());
		wPlaylist = wSong.c_str();

		textNode = xmlDoc->createTextNode(wPlaylist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	return xmlDoc;
}


/*method to validate user input of type integer*/
int XMLDomWritter::checkUserInput() {
	int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}

string XMLDomWritter::getChildByName(const char* parentTag, const char* childTag,const char* childValue){
	const char* attributeTag = "ID";
	string value;
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);
	for (int parentIndex = 0; parentIndex <(int)list->getLength() ;parentIndex++){
		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		DOMElement* child =
				dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(0));
		if (child) {
			const char* temp = XMLString::transcode(child->getTextContent());
			if (strcmp(childValue,temp) == 0){
				XMLCh* temp1 = XMLString::transcode("ID");
				char* temp2 = XMLString::transcode(parent->getAttribute(temp1));
				value =  temp2;
				break;
			}
		}
	}
	if (value.empty()){
		value = getChildByName(parentTag, childTag, "None");
	}
	return value;
}


int XMLDomWritter::getID(const char* parentTag, const char* childTag){
	const char* attributeTag = "ID";
	int parentIndex = 0;
	const char* value;
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);
	while (true){
		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		temp = XMLString::transcode(attributeTag);
		char* temp2 = XMLString::transcode(parent->getAttribute(temp));
	}
	return 0;
}