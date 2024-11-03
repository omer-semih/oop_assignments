import java.util.ArrayList;
import java.util.List;

// Base class for all media objects
abstract class Media {
    String name;
    String otherInfo;

    Media(String name, String otherInfo) {
        this.name = name;
        this.otherInfo = otherInfo;
    }

    abstract void info();
}

// Interfaces for different media types
interface Playable {
    void play();
}

interface NonPlayable {
    void view();
}

interface Visual {}

interface NonVisual {}

// Derived classes for specific media types
// Define the Image class, which is a type of Media and implements NonPlayable and Visual interfaces
class Image extends Media implements NonPlayable, Visual {
    String dimensions;  // Stores the dimensions of the image

    // Constructor to initialize Image object with name, dimensions, and other info
    Image(String name, String dimensions, String otherInfo) {
        super(name, otherInfo);  // Call the constructor of the superclass Media
        this.dimensions = dimensions;
    }

    // Method to view the image
    public void view() {
        System.out.println("Viewing image: " + name);
    }

    // Method to display information about the image
    public void info() {
        System.out.println("Image: " + name + ", Dimensions: " + dimensions + ", Other Info: " + otherInfo);
    }
}

// Define the Audio class, which is a type of Media and implements Playable and NonVisual interfaces
class Audio extends Media implements Playable, NonVisual {
    String duration;  // Stores the duration of the audio

    // Constructor to initialize Audio object with name, duration, and other info
    Audio(String name, String duration, String otherInfo) {
        super(name, otherInfo);  // Call the constructor of the superclass Media
        this.duration = duration;
    }

    // Method to play the audio
    public void play() {
        System.out.println("Playing audio: " + name);
    }

    // Method to display information about the audio
    public void info() {
        System.out.println("Audio: " + name + ", Duration: " + duration + ", Other Info: " + otherInfo);
    }
}

// Define the Video class, which is a type of Media and implements Playable and Visual interfaces
class Video extends Media implements Playable, Visual {
    String duration;  // Stores the duration of the video

    // Constructor to initialize Video object with name, duration, and other info
    Video(String name, String duration, String otherInfo) {
        super(name, otherInfo);  // Call the constructor of the superclass Media
        this.duration = duration;
    }

    // Method to play the video
    public void play() {
        System.out.println("Playing video: " + name);
    }

    // Method to display information about the video
    public void info() {
        System.out.println("Video: " + name + ", Duration: " + duration + ", Other Info: " + otherInfo);
    }
}

// Define the Text class, which is a type of Media and implements NonPlayable and NonVisual interfaces
class Text extends Media implements NonPlayable, NonVisual {
    // Constructor to initialize Text object with name and other info
    Text(String name, String otherInfo) {
        super(name, otherInfo);  // Call the constructor of the superclass Media
    }

    // Method to view the text
    public void view() {
        System.out.println("Viewing text: " + name);
    }

    // Method to display information about the text
    public void info() {
        System.out.println("Text: " + name + ", Other Info: " + otherInfo);
    }
}


// Observer interface and classes
interface Observer {
    void update(Media media);
}

// Define the Player class which implements the Observer interface
class Player implements Observer {
    List<Playable> playlist = new ArrayList<>(); // List to store playable media
    private int currentPlayingIndex = 0; // Index of the currently playing item

    // Method called when the observed object is changed
    public void update(Media media) { 
        if(media != null) {
        if (media instanceof Playable) {
            playlist.add((Playable) media);
        } else if (media == null) { // Handle removal
            // This condition will never be true, null media cannot be compared.
            return;
        }
        }
    }

    // Method to remove a media item from the playlist
    public void removeFromPlaylist(Playable media) {
        playlist.remove(media);

        // Reset the index if the viewList is empty
        if (!playlist.isEmpty() && currentPlayingIndex >= playlist.size()) {
            currentPlayingIndex = 0; 
        }
    }

    // Method to show the list of media items in the playlist
    public void show_list() {
        try {
        if (playlist.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return;
        }
        // Print the playlist items
        for (int i = 0; i < playlist.size(); i++) {
            System.out.println((i + 1) + ". " + playlist.get(i).getClass().getSimpleName() + ": " + ((Media) playlist.get(i)).name);
        }
    }

    // Method to get the currently playing media item
    public Playable currently_playing() {
        try {
        if (playlist.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return null;
        }

        return playlist.get(currentPlayingIndex);
    }

    // Method to skip to the next media item of a specific type in the playlist
    public void next(String type) {
        try {
        if (playlist.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return;
        }

        boolean found = false;
        int originalIndex = currentPlayingIndex;
        do {
            currentPlayingIndex = (currentPlayingIndex + 1) % playlist.size();
            if (playlist.get(currentPlayingIndex).getClass().getSimpleName().equalsIgnoreCase(type)) {
                found = true; // If the item matches the type, mark as found
            }
        } while (currentPlayingIndex != originalIndex && !found); // Stop if we've looped back or found a match

        if (!found) { // Print a message if no match is found
            System.out.println("No media of type " + type + " found in the playlist."); 
        }
    }

    // Method to skip to the previous media item of a specific type in the playlist
    public void previous(String type) {
        try {
        if (playlist.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return;
        }

    boolean found = false;
    int originalIndex = currentPlayingIndex;
    do {
        currentPlayingIndex = (currentPlayingIndex - 1 + playlist.size()) % playlist.size();
        if (playlist.get(currentPlayingIndex).getClass().getSimpleName().equalsIgnoreCase(type)) {
            found = true; // If the item matches the type, mark as found
        }
    } while (currentPlayingIndex != originalIndex && !found); // Stop if we've looped back or found a match

    if (!found) { // Print a message if no match is found
        System.out.println("No media of type " + type + " found in the playlist.");
    }
    }
}

// Define the Viewer class which implements the Observer interface
class Viewer implements Observer {
    List<NonPlayable> viewList = new ArrayList<>();
    private int currentViewingIndex = 0; // Index of the currently viewing item

    // Method called when the observed object is changed
    public void update(Media media) {
        if(media != null) {
        if (media instanceof NonPlayable) {
            viewList.add((NonPlayable) media);
        } else if (media == null) { // Handle removal
            // This condition will never be true, null media cannot be compared.
            return;
        }
        }
    }

    // Method to remove a media item from the viewList
    public void removeFromViewList(NonPlayable media) {
        viewList.remove(media);

        // Reset the index if the viewList is empty
        if (!viewList.isEmpty() && currentViewingIndex >= viewList.size()) {
            currentViewingIndex = 0; 
        }
    }

    // Method to show the list of media items in the viewList
    public void show_list() {
        try {
        if (viewList.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return;
        }
        // Print the viewList items
        for (int i = 0; i < viewList.size(); i++) {
            System.out.println((i + 1) + ". " + viewList.get(i).getClass().getSimpleName() + ": " + ((Media) viewList.get(i)).name);
        }
    }

    // Method to get the currently viewing media item
    public NonPlayable currently_viewing() {
        try {
        if (viewList.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return null;
        }

        return viewList.get(currentViewingIndex); // Return the currently viewing media item
    }

    // Method to skip to the next media item of a specific type in the viewList
    public void next(String type) {
        try {
        if (viewList.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return;
        }

        boolean found = false;
        int originalIndex = currentViewingIndex;
        do {
        currentViewingIndex = (currentViewingIndex + 1) % viewList.size();
        if (viewList.get(currentViewingIndex).getClass().getSimpleName().equalsIgnoreCase(type)) {
            found = true; // If the item matches the type, mark as found
        }
        } while (currentViewingIndex != originalIndex && !found); // Stop if we've looped back or found a match

        if (!found) {
        System.out.println("No media of type " + type + " found in the viewList."); // Print a message if no match is found
        }
    }

    // Method to skip to the previous media item of a specific type in the viewList
    public void previous(String type) {
        
        try {
        if (viewList.isEmpty()) throw new Exception("The list is empty.");
        } catch (Exception e) {
            System.out.println(e); // Print the exception message
            return;
        }

        boolean found = false;
        int originalIndex = currentViewingIndex;
        do {
        currentViewingIndex = (currentViewingIndex - 1 + viewList.size()) % viewList.size();
        if (viewList.get(currentViewingIndex).getClass().getSimpleName().equalsIgnoreCase(type)) {
            found = true; // If the item matches the type, mark as found
        }
        } while (currentViewingIndex != originalIndex && !found); // Stop if we've looped back or found a match

        if (!found) {
        System.out.println("No media of type " + type + " found in the viewList."); // Print a message if no match is found
        }
    }
}

// Dataset class
class Dataset {
    List<Media> items = new ArrayList<>(); // List to store media items
    List<Observer> observers = new ArrayList<>(); // List to store observers

    // Method to add a media item to the dataset
    void add(Media media) {
        items.add(media);
        notifyObservers(media); // Notify all observers about the new media item
    }

    // Method to remove a media item from the dataset
    void remove(Media media) {
        items.remove(media);
        notifyObserversRemoval(media); // Notify observers about the removal
    }

    // Method to register a new observer
    void register(Observer observer) {
        observers.add(observer);
        // When an observer is registered, update it with the existing items
        for (Media item : items) {
            observer.update(item);
        }
    }

    // Method to remove an observer from the list
    void remove_observer(Observer observer) {
        observers.remove(observer);
    }

    // Private method to notify all observers about a new media item
    private void notifyObservers(Media media) {
        for (Observer observer : observers) {
            observer.update(media); // Notify each observer about the new media item
        }
    }

    // Private method to notify all observers about the removal of a media item
    private void notifyObserversRemoval(Media media) {
        for (Observer observer : observers) {
            // Check the type of media and the type of observer to handle removal accordingly
            if (media instanceof Playable && observer instanceof Player) {
                // Notify player to remove the media item from the playlist
                ((Player) observer).removeFromPlaylist((Playable) media);
            } else if (media instanceof NonPlayable && observer instanceof Viewer) {
                // Notify viewer to remove the media item from the view list
                ((Viewer) observer).removeFromViewList((NonPlayable) media);
            }
        }
    }
}

// Main class for testing
public class Main {
    public static void main(String[] args) {

        //It creates a new Dataset object
        Dataset ds = new Dataset();

        //It creates new player and viewer objects
        Player p1 = new Player();
        Player p2 = new Player();
        Viewer v1 = new Viewer();
        Viewer v2 = new Viewer();

        //Player and Viewer objects are registered to dataset object
        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        ds.register(v2);

        //Image, Text, Audio and Video objects are added to Dataset object
        ds.add(new Image("image1", "1920 x 1080", "nature"));
        ds.add(new Image("image2", "1280 x 720", "portrait"));
        ds.add(new Image("image3", "3840 x 2160", "street"));
        ds.add(new Image("image4", "2560 x 1440", "wildlife"));
        ds.add(new Image("image5", "1366 x 768", "underwater"));

        ds.add(new Video("video1", "5:57:24", "vlog"));
        ds.add(new Video("video2", "2:45:12", "movie"));
        ds.add(new Video("video3", "3:13:36", "series"));

        ds.add(new Text("text1", "diary"));
        ds.add(new Text("text2", "blog"));
        ds.add(new Text("text3", "news"));
        
        ds.add(new Audio("audio1", "4:08:59", "rap"));
        ds.add(new Audio("audio2", "1:32:45", "pop"));
        ds.add(new Audio("audio3", "7:21:48", "rock"));
        

        //Prints the whole items of playlist
        p1.show_list();
        p2.show_list();
        
        //Prints the whole items of viewlist
        v1.show_list();
        v2.show_list();
        
        // Play the currently playing object
        Playable po = p1.currently_playing();
        if (po != null) {
            po.play();
            ((Media) po).info();
        }

        //Play the currently playing object
        po = p2.currently_playing();
        if (po != null) {
            po.play();
            ((Media) po).info();
        }

        //View the currently viewing object
        NonPlayable np = v1.currently_viewing();
        if (np != null) {
            np.view();
            ((Media) np).info();
        }

        //View the currently viewing object
        np = v2.currently_viewing();
        if (np != null) {
            np.view();
            ((Media) np).info();
        }

        
        //The currently played playing object is removed from playlist
        if (po != null) {
            ds.remove((Media) po);
        }
        
        //The currently played playing object is removed from playlist
        if (np != null) {
            ds.remove((Media) np);
        }

        po = p1.currently_playing(); // Get currenly playing media item
        np = v1.currently_viewing(); // Get currenly playing media item

        if (po != null) {
            po.play();
            ((Media) po).info();
        }

        if (np != null) {
            np.view();
            ((Media) np).info();
        }

        // Skip some items for testing player 1
        p1.next("Video");
        p1.next("Video");
        p1.next("Audio");

        // TEST
        po = p1.currently_playing();
        if (po != null) {
            po.play();
            ((Media) po).info();
        }

        // Tests for player 2
        p2.next("Audio");
        p2.previous("Audio");

        po = p2.currently_playing();
        if (po != null) {
            po.play();
            ((Media) po).info();
        }

        // Tests for viewer 1
        v1.previous("Text");
        v1.previous("Text");

        np = v1.currently_viewing();
        if (np != null) {
            np.view();
            ((Media) np).info();
        }

        // Tests for viewer 2
        v2.next("Text");
        v2.next("Text");
        v2.previous("Image");
        

        np = v2.currently_viewing();
        if (np != null) {
            np.view();
            ((Media) np).info();
        }


        //Prints the whole items of playlist
        System.out.println("\nPlayer 1's playlist :");
        p1.show_list();

        System.out.println("\nPlayer 2's playlist :");
        p2.show_list();

        //Prints the whole items of viewlist
        System.out.println("\nViever 1's viewlist :");
        v1.show_list();

        System.out.println("\nViever 2's viewlist :");
        v2.show_list();

        // Remove all observers from the dataset
        ds.remove_observer(p1);
        ds.remove_observer(p2);
        ds.remove_observer(v1);
        ds.remove_observer(v2);

    }
}