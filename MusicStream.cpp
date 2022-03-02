#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    Profile abc(email, username, plan);
    profiles.insertAtTheEnd(abc);
}

void MusicStream::deleteProfile(const std::string &email) {
    // TODO
    Node<Profile> *ptr0;
    Node<Profile*> *ptr1;
    Node<Profile*> *ptr2;
    Node<Profile*> *ptr3;
    Node<Playlist> *ptr4;

    // find the first user in profiles list
    // ptr0 will point to the first profile's node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the first user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // the profile that we will delete will be unfollowed by its followers (remove us from their followings list)
    // ptr1 will point to the first follower's node of the followers list of the profile
    ptr1 = (ptr0->data).getFollowers().getFirstNode();
    // traverse the whole followers list
    do {
        // reach to followers' profiles and make them unfollow us
        (*(ptr1->data)).unfollowProfile( &(ptr0->data) );
        // take a step
        ptr1 = ptr1->next;
    } while ( ptr1 != (ptr0->data).getFollowers().getFirstNode() );

    // the profile that we will delete will unfollow its followings (remove us from their followers list)
    // ptr2 will point to the first followings's node in the following list of the profile
    ptr2 = (ptr0->data).getFollowings().getFirstNode();
    // traverse the whole following list
    do {
        // reach the profiles in the following list and remove us from their followers list
        // ptr3 will point to the first follower's node of the followers list of my following
        ptr3 = (*(ptr2->data)).getFollowers().getFirstNode();
        // go to us from the followers list
        do {
            
            if ( (*(ptr3->data)).getEmail() == (ptr0->data).getEmail() ) {
                (*(ptr2->data)).getFollowers().removeNode(ptr3->data);
                break;
            }
            
            else {
                // take a step
                ptr3 = ptr3->next;
            }
        } while ( (*(ptr3->data)).getEmail() == (ptr0->data).getEmail() );
        (*(ptr2->data)).getFollowers().removeNode(ptr3->data);
        // take a step
        ptr2 = ptr2->next;
    } while ( ptr2 != (ptr0->data).getFollowings().getFirstNode() );

    // takip ettiklerimi sil
    (ptr0->data).getFollowings().removeAllNodes();

    // takip edenlerin listesini sil
    (ptr0->data).getFollowers().removeAllNodes();

    // delete songs list in the playlist !!!!!!!!!!!!!1
    // ptr4 will point to the first node of the playlists of our profiles playlists list
    ptr4 = (ptr0->data).getPlaylists().getFirstNode();
    do {
        // delete all songs of the playlist
        (ptr4->data).getSongs().removeAllNodes();
        // take a step
        ptr4 = ptr4->next;
    } while ( ptr4 != (ptr0->data).getPlaylists().getFirstNode() );

    // delete playlists of the profile
    (ptr0->data).getPlaylists().removeAllNodes();

    // delete the profile from the profiles list in the music stream
    (this->profiles).removeNode(ptr0);

}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    // create a new artist with the given name
    Artist newArtist(artistName);
    // add this artist to the music streams artists list
    (this->artists).insertAtTheEnd(newArtist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    Album *albumPtr;
    Node<Artist> *ptr1;
    // create a new album with the given name
    Album newAlbum(albumName);

    // add the album to the music stream's albums list
    (this->albums).insertAtTheEnd(newAlbum);
    
    // now, find the artist who has this album
    // ptr1 will point to the first artist's node in the artists list
    ptr1 = (this->artists).getFirstNode();
    
    // go to the correct artist's node in artists list
    while ( (ptr1->data).getArtistId() != artistId ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, you are pointing to the correct artist's node in the artists list

    // assign a pointer to the address of the album
    albumPtr = &(((this->albums).getLastNode())->data);

    // add this album to the artists albums list
    (ptr1->data).addAlbum(albumPtr);
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    Node<Album> *ptr0;
    // create a new song with the given name and duration
    Song newSong(songName, songDuration);
    // add this new song to the music stream's songs list
    (this->songs).insertAtTheEnd(newSong);

    // add the song to the music stream's correct album's songs list
    // ptr0 will point to the first album's node in the albums list of the music stream
    ptr0 = (this->albums).getFirstNode();
    // go to the node whose data is album of albumId
    while ( (ptr0->data).getAlbumId() != albumId ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, you are pointing to the album's node which has the correct albumId
    (ptr0->data).addSong( ( &( (this->songs).getLastNode() )->data ) );
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    // TODO
    Node<Profile> *ptr0;
    Node<Profile> *ptr1;

    // find the first user in profiles list
    // ptr0 will point to the first profile's node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the first user by traversing
    while ( (ptr0->data).getEmail() != email1 ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email1 as its email address

    // find the second user in profiles list
    // ptr1 will point to the first profile's node in the profiles list of the music stream
    ptr1 = (this->profiles).getFirstNode();
    // go to the second user by traversing
    while ( (ptr1->data).getEmail() != email2 ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, ptr1 is pointing to the node of the profile which has email2 as its email address

    // add the second profile to the first profile's following list
    (ptr0->data).followProfile( &(ptr1->data) );

    // add the first profile to the second profile's followers list
    (ptr1->data).getFollowers().insertAtTheEnd( &(ptr0->data) );

}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    // TODO
    Node<Profile> *ptr0;
    Node<Profile> *ptr1;

    // find the first user in profiles list
    // ptr0 will point to the first profile's node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the first user by traversing
    while ( (ptr0->data).getEmail() != email1 ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email1 as its email address

    // find the second user in profiles list
    // ptr1 will point to the first profile's node in the profiles list of the music stream
    ptr1 = (this->profiles).getFirstNode();
    // go to the second user by traversing
    while ( (ptr1->data).getEmail() != email2 ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, ptr1 is pointing to the node of the profile which has email2 as its email address

    // remove the second profile from the first profile's following list
    (ptr0->data).unfollowProfile( &(ptr1->data) );

    // remove the first profile from the second profile's followers list
    (ptr1->data).getFollowers().removeNode( &(ptr0->data) );
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    // TODO
    // create a new playlist with the given name
    Playlist newPlaylist(playlistName);
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list
    // ptr0 will point to the profile's first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // add this new playlist to the profiles playlists list
    (ptr0->data).getPlaylists().insertAtTheEnd(newPlaylist);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    // TODO
    Node<Playlist> *ptr1;
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list
    // ptr0 will point to the profile's first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // find the playlist with given playlistId in the playlists list of this profile
    // ptr1 will point to the playlists' first node in the playlists of the profile with the given email
    ptr1 = (ptr0->data).getPlaylists().getFirstNode();
    // go to the playlist with the given playlistId by traversing
    while ( (ptr1->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now ptr1 is pointing to the node of the playlist which has the given playlistId

    // YOU MAY WANT TO USE THE OTHER VERSION OF REMOVENODE HERE!!!!!!!!!!!
    (ptr0->data).getPlaylists().removeNode(ptr1);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    // TODO
    Node<Profile> *ptr0;
    Node<Song> *ptr1;
    Node<Playlist> *ptr2;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // find the song with the given songId in songs list of the music stream
    // ptr1 will point to the songs' first node in the songs list of the music stream
    ptr1 = (this->songs).getFirstNode();
    // go to that song by traversing
    while ( (ptr1->data).getSongId() != songId ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, ptr1 is pointing to the node of the song with the given songId

    // find the playlist with given playlistId in the playlists list of this profile
    // ptr2 will point to the playlists' first node in the playlists of the profile with the given email
    ptr2 = (ptr0->data).getPlaylists().getFirstNode();
    // go to the playlist with the given playlistId by traversing
    while ( (ptr2->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr2 = ptr2->next;
    }
    // now, ptr2 is pointing to the node of the playlist which has the given playlistId

    // add this song to this playlist
    (ptr2->data).getSongs().insertAtTheEnd( &(ptr1->data) );
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    // TODO
    Node<Profile> *ptr0;
    Node<Playlist> *ptr1;
    Node<Song*> *ptr2;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // find the playlist with given playlistId in the playlists list of this profile
    // ptr1 will point to the playlists' first node in the playlists of the profile with the given email
    ptr1 = (ptr0->data).getPlaylists().getFirstNode();
    // go to the playlist with the given playlistId by traversing
    while ( (ptr1->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, ptr1 is pointing to the node of the playlist which has the given playlistId

    // find the song with the given id from the playlist with the given playlisId
    // ptr2 will point to the songs' first node in the songs list of the playlist with the given playlistId
    ptr2 = (ptr1->data).getSongs().getFirstNode();
    // go to the song by traversing
    while ( (*(ptr2->data)).getSongId() != songId ) {
        // take a step
        ptr2 = ptr2->next;
    }
    // now, ptr2 is pointing to the node of the song pointer to the song with the given songId


    // remove that song from the playlist
    (ptr1->data).getSongs().removeNode(ptr2);

}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    // TODO
    Node<Profile> *ptr0;
    Node<Song*> *ptr1;
    Song a("advertisement", 30);

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // if the user has premium
    if ( (ptr0->data).getPlan() == premium ) {
        // return the songs inside it as they are
        return (*playlist).getSongs();
    }
    // if the user has not premium
    else {
        // place advertisement after every node of songs
        // ptr1 will point to the songs' first node in the songs list of the given playlist
        ptr1 = (*playlist).getSongs().getFirstNode();
        do {
            // insert advertisement song after the node pointed by ptr1
            (*playlist).getSongs().insertAfterNode( &a , ptr1);// !!!!!!!!!!!!!!!!!!!!!!!!!
            // take two step
            ptr1 = ptr1->next->next;
        } while (ptr1 != (*playlist).getSongs().getFirstNode());
        // BURADA BİZE VERİLEN PLAYLİSTİ DEĞİŞTİRİYORUZ. EĞER DEĞİŞTİRMEMEMİZ GEREKİYORSA COPY CONSTRUCTOR KULLANARAK İÇERİĞİNİ BİR BAŞKA PLAYLİSTE KOPYALAYIP ONA ADVERTİSEMENT EKLEYİP ONU RETURN ET. BÖYLECE BİZE VERİLEN PLAYLİSTİN ŞARKILARI DEĞİŞMEYECEK!
        // ÜSTTEKİNİN TAM TERSİNİ YAPTIK!!!!!!
        return (*playlist).getSongs();
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    // TODO
    Node<Profile> *ptr0;
    Node<Playlist> *ptr1;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // find the playlist with given playlistId in the playlists list of this profile
    // ptr1 will point to the playlists' first node in the playlists of the profile with the given email
    ptr1 = (ptr0->data).getPlaylists().getFirstNode();
    // go to the playlist with the given playlistId by traversing
    while ( (ptr1->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, ptr1 is pointing to the node of the playlist which has the given playlistId

    return &(ptr1->data);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    // TODO
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    
    LinkedList<Playlist *> sharedPlaylists( (ptr0->data).getSharedPlaylists() );
    // return it
    return sharedPlaylists;
    
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    // TODO
    Node<Profile> *ptr0;
    Node<Playlist> *ptr1;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // find the playlist with given playlistId in the playlists list of this profile
    // ptr1 will point to the playlists' first node in the playlists of the profile with the given email
    ptr1 = (ptr0->data).getPlaylists().getFirstNode();
    // go to the playlist with the given playlistId by traversing
    while ( (ptr1->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr1 = ptr1->next;
    }
    // now, ptr1 is pointing to the node of the playlist which has the given playlistId

    // shuffle the playlist with the given playlistId
    (ptr1->data).shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    // TODO
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // share this playlist
    (ptr0->data).sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    // TODO
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    // share this playlist
    (ptr0->data).unsharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email) {
    // TODO
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    (ptr0->data).setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    // TODO
    Node<Profile> *ptr0;

    // find the user with the given email in profiles list of the music stream
    // ptr0 will point to the profiles' first node in the profiles list of the music stream
    ptr0 = (this->profiles).getFirstNode();
    // go to the user by traversing
    while ( (ptr0->data).getEmail() != email ) {
        // take a step
        ptr0 = ptr0->next;
    }
    // now, ptr0 is pointing to the node of the profile which has email as its email address

    (ptr0->data).setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
