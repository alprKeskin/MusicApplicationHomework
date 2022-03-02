#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    // TODO
    // add a node, whose data is a profile pointer, to the following linked list
    (this->following).insertAtTheEnd(profile);
    
}

void Profile::unfollowProfile(Profile *profile) {
    // TODO
    // remove node, whose data is a profile pointer, to the following linked list
    (this->following).removeNode(profile);

}

// we did not set playlist id !!!!!!!!!!!!!!!
void Profile::createPlaylist(const std::string &playlistName) {
    // TODO
    // create a new playlist with the given name
    Playlist newPlaylist(playlistName);
    // add that playlist to the playlists of the profile
    (this->playlists).insertAtTheEnd(newPlaylist);
}

void Profile::deletePlaylist(int playlistId) {
    // TODO
    Node<Playlist> *current;

    // current will point to the first node
    current = (this->playlists).getFirstNode();

    // go to the correct node
    while ((current->data).getPlaylistId() != playlistId) {
        // take a step
        current = current->next;
    }

    // now, current points to the correct node
    // remove this node !!!!!!!!!!!!!!!!!!!!!!!!!!
    (this->playlists).removeNode(current->data);

}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    // TODO
    Node<Playlist> *current;

    // current will point to the first node
    current = (this->playlists).getFirstNode();

    // go to the correct node
    while ((current->data).getPlaylistId() != playlistId) {
        // take a step
        current = current->next;
    }
    // now, current points to the correct node

    // add a new song to the playlist which is the data of the current node
    (current->data).addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    // TODO
    Node<Playlist> *current;

    // current will point to the first node
    current = (this->playlists).getFirstNode();

    // go to the correct node
    while ((current->data).getPlaylistId() != playlistId) {
        // take a step
        current = current->next;
    }
    // now, current points to the correct node

    // remove the song from the playlist which is the data of the current node
    (current->data).dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId) {
    // TODO
    Node<Playlist> *current;

    // current will point to the first node
    current = (this->playlists).getFirstNode();

    // go to the correct node
    while ((current->data).getPlaylistId() != playlistId) {
        // take a step
        current = current->next;
    }
    // now, current points to the correct node
    // return the address of that playlist
    return &(current->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    // TODO
    Node<Profile *> *ptr0;
    Node<Playlist> *ptr1;
    LinkedList<Playlist *> sharedPlaylists;

    // ptr0 will point to the first follower
    ptr0 = (this->following).getFirstNode();

    // traverse the following list
    do {
        // ptr1 will point to the first playlist of that follower
        ptr1 = (ptr0->data->playlists).getFirstNode();
        // traverse the playlists of that follower
        do {
            // if this playlist is shared
            if ( (ptr1->data).isShared() == true ) {
                // add it to our sharedPlayList
                sharedPlaylists.insertAtTheEnd(&(ptr1->data));
                // take a step
                ptr1 = ptr1->next;
            }

            // if this playlist is not shared
            else {
                // take a step
                ptr1 = ptr1->next;
            }
        } while ( ptr1 != (ptr0->data->playlists).getFirstNode() );
        // take step in the following list
        ptr0 = ptr0->next;
    } while ( ptr0 != (this->following).getFirstNode() );
    return sharedPlaylists;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    // TODO
    Node<Playlist> *ptr0;

    // ptr0 will point to the first playlist of that follower
    ptr0 = (this->playlists).getFirstNode();

    // go to correct playlist node in the playlists of the profile
    while ( (ptr0->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr0 = ptr0->next;
    }
    
    (ptr0->data).shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {
    // TODO
    Node<Playlist> *ptr0;

    // ptr0 will point to the first playlist of that follower
    ptr0 = (this->playlists).getFirstNode();

    // go to correct playlist node in the playlists of the profile
    while ( (ptr0->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr0 = ptr0->next;
    }

    // share it
    (ptr0->data).setShared(true);
}

void Profile::unsharePlaylist(int playlistId) {
    // TODO
    Node<Playlist> *ptr0;

    // ptr0 will point to the first playlist of that follower
    ptr0 = (this->playlists).getFirstNode();

    // go to correct playlist node in the playlists of the profile
    while ( (ptr0->data).getPlaylistId() != playlistId ) {
        // take a step
        ptr0 = ptr0->next;
    }

    // share it
    (ptr0->data).setShared(false);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
