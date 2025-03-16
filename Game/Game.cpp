/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#include "Game.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <thread>
#include <chrono>

// constructor initialization
Game::Game() {
    srand(time(0));
    cmds = setup_commands();
    create_world();
    current_location = random_location();
    current_location->set_Visited();
    current_weight = 0;
    elf_calories_needed = 500;
    in_progress = true;
}

// initialize the commands map
std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setup_commands() {
    std::map<std::string, void(Game::*)(std::vector<std::string>)> cmds;
    cmds["cmd"] = &Game::show_Help;
    cmds["cmds"] = &Game::show_Help;
    cmds["info"] = &Game::show_Help;
    cmds["help"] = &Game::show_Help;
    cmds["?"] = &Game::show_Help;
    cmds["g"] = &Game::guide;
    cmds["guide"] = &Game::guide;
    cmds["look"] = &Game::look;
    cmds["meet"] = &Game::meet;
    cmds["i"] = &Game::show_items;
    cmds["inventory"] = &Game::show_items;
    cmds["take"] = &Game::take;
    cmds["give"] = &Game::give;
    cmds["talk"] = &Game::talk;
    cmds["quest"] = &Game::quest;
    cmds["q"] = &Game::quest;
    cmds["teleport"] = &Game::teleport;
    cmds["tp"] = &Game::teleport;
    cmds["go"] = &Game::go;
    cmds["quit"] = &Game::quit;
    return cmds;
}

// creates the game world
void Game::create_world() {
    
    // creates locations for the game world
    Location* obsidian_hall = new Location("The Obsidian Hall", "This cavernous hall is cloaked in\n"
    "eternal darkness, with walls formed of jagged black obsidian that catch the faint,\n"
    "flickering glow of distant embers. The air smells of burnt stone, and the floor beneath you\n"
    "crunches with shards of brittle glass. To the south, a faint shimmering light pours through an\n"
    "archway carved with ancient runes, leading to The Crystal Sanctum."
    );
    
    Location* crystal_sanctum = new Location("The Crystal Sanctum", "A dazzling array of enormous crystals\n"
    "pierce through the walls and ceiling, refracting multicolored light in hypnotic patterns that dance\n"
    "across the chamber. The air hums faintly, and you can feel the vibrations through your chest.\n"
    "To the north, a darkened corridor slopes upward to the jagged shadows of The Obsidian Hall.\n"
    "To the south, an incline leads downward into the ominous whispers of The Whispering Cavern."
    );
        
    Location* fallen_library = new Location("The Fallen Library", "The remains of a once-mighty library stand\n"
    "crumbling here. Towers of books sag precariously, their pages faded to ash-gray, while the scent of\n"
    "musty paper hangs in the stagnant air. Broken wooden chairs and toppled shelves litter the space.\n"
    "To the south, a vine-covered passage descends into the tranquil, eerie Pool of Stillness,\n"
    "while to the north, a shadowy corridor rises into the blazing heat of The Infernal Forge."
    );
        
    Location* pool = new Location("The Pool of Stillness", "At the center of this hauntingly quiet chamber\n"
    "lies a still, mirror-like pool of black water that reflects the glowing fungi creeping\n"
    "across the ceiling. Occasional ripples distort the reflection without any apparent cause.\n"
    "To the north, a narrow passage rises into the crumbling ruins of The Fallen Library,\n"
    "while to the south, a shadowy path winds back into the dense, foreboding Woods."
    );        
    
    Location* cavern = new Location("The Whispering Cavern", "Twisting tunnels converge into this chamber,\n"
    "where the walls are carved with grotesque, screaming faces.\n"
    "Despite their silent appearance, whispers echo through the room,\n"
    "growing louder as you approach the center. To the west, a narrow passage leads into\n"
    "the dense, shadowy expanse of The Woods. To the north, an incline twists upward into\n"
    "the mesmerizing lights of The Crystal Sanctum. To the south, a jagged tunnel descends\n"
    "into the searing heat of The Infernal Forge."
    );        
    
    Location* infernal_forge = new Location("The Infernal Forge", "This chamber radiates with searing heat,\n"
    "its heart dominated by a glowing forge etched with demonic symbols.\n"
    "Broken weaponry and armor are scattered across the floor,\n"
    "some appearing to have melted into the stone itself.\n"
    "To the east, a fiery passage leads into the swirling void of The Abyssal Gate.\n"
    "To the north, a shadowy tunnel climbs into the eerie whispers of The Cavern,\n"
    "and to the south, a sloped corridor descends into the crumbling ruins of The Fallen Library."
    );        
    
    Location* shrine = new Location("The Hollow Shrine", "Shadows linger heavily in this desolate chamber,\n"
    "where a broken altar stands shrouded in dust and cobwebs.\n"
    "The rooms air is thick with despair, and faint symbols glow dimly along the cracked pillars.\n"
    "To the east, a narrow pathway twists into the dense, shadowy Woods,\n"
    "and to the west, a crumbling stone corridor opens into the ominous Abyssal Gate."
    );        
    
    Location* gate = new Location("The Abyssal Gate", "The central chamber of the dungeon is a massive,\n"
    "yawning void interrupted only by a swirling portal of black and purple light.\n"
    "The walls seem to dissolve into nothingness as you approach, and dark tendrils of energy radiate outward,\n"
    "leaving the ground around them cracked and lifeless.\n"
    "To the north, the towering trees of The Woods loom. To the east,\n"
    "a narrow corridor leads into the desolate Hollow Shrine, and to the west,\n"
    "a fiery staircase descends back into the searing depths of The Infernal Forge."
    );
        
    Location* woods = new Location("The Woods", "A dense, labyrinthine forest overtaken by twisting,\n"
    "gnarled trees that claw at the sky. Shadows stretch unnaturally along the moss-covered ground,\n"
    "and faint, echoing growls seem to come from nowhere. To the east, a tangled path slopes downward\n"
    "into the eerie whispers of The Whispering Cavern. To the west, a crumbling wooden bridge arches\n"
    "into the desolate Hollow Shrine. To the north, an overgrown tunnel leads into the stillness\n"
    "of The Pool of Stillness, and to the south, the towering trees part to reveal the ominous Abyssal Gate."
    );         

    // sets up the directions to traverse to with game locations
    woods->add_Location("east", cavern);
    cavern->add_Location("west", woods);

    woods->add_Location("west", shrine);    
    shrine->add_Location("east", woods);

    woods->add_Location("north", pool);
    pool->add_Location("south", woods);

    woods->add_Location("south", gate);
    gate->add_Location("north", woods);

    fallen_library->add_Location("south", pool);
    pool->add_Location("north", fallen_library);

    fallen_library->add_Location("north", infernal_forge);
    infernal_forge->add_Location("south", fallen_library);

    cavern->add_Location("north", crystal_sanctum);
    crystal_sanctum->add_Location("south", cavern);

    infernal_forge->add_Location("north", cavern);
    cavern->add_Location("south", infernal_forge);

    shrine->add_Location("west", gate);
    gate->add_Location("east", shrine);

    gate->add_Location("west", infernal_forge);
    infernal_forge->add_Location("east", gate);

    obsidian_hall->add_Location("south", crystal_sanctum);
    crystal_sanctum->add_Location("north", obsidian_hall);

    
    // create NPCs
    NPC eryndor("Eryndor, the Enigmatic Sylvan", "Nestled within the eerie shadows of The Woods,\n"
    "Eryndor sits cross-legged atop a moss-covered stone, his slender frame\n"
    "swathed in tattered gray-green robes that blend seamlessly with the forest.\n"
    "His ashen, angular face is illuminated by faintly glowing violet eyes,\n"
    "which seem to pierce your very soul. Long, jet-black hair flows down his back,\n"
    "streaked with strands of silver that shimmer in the dim light of bioluminescent fungi."
    );

    eryndor.add_Message("Long ago, the balance of this realm was shattered, "
    "unleashing chaos into our lands. The ancient guardians have slumbered ever since."
    );

    eryndor.add_Message("The forests grow darker with every passing day, "
    "their whispers warning of an approaching calamity. Soon, not even this glade will be safe."
    );

    eryndor.add_Message("The black tendrils you may have seen... "
    "they feed on the essence of this world. If left unchecked, they will consume all that lives."
    );

    eryndor.add_Message("I... I possess the knowledge to push back the corruption, "
    "but my strength fades with time. Only through nourishment can I act."
    );

    eryndor.add_Message("Bring me sustenance from the lands you traverse, "
    "and perhaps this realm may yet see salvation... or its doom, should you falter."
    );

    NPC vaylin("Vaylin, the Forsaken Seer", "A frail, hooded figure sits hunched beneath\n"
    "the glowing fungi of The Pool of Stillness. Her eyes, once radiant,\n"
    "are now clouded over, yet she claims to see far beyond mortal comprehension.\n"
    "Wrapped in tattered robes and clutching a staff made of twisted blackwood,\n"
    "she emanates an aura of foreboding wisdom."
    );

    vaylin.add_Message("The waters whisper to me of shadows creeping closer... "
    "They consume what they touch, leaving naught but silence."
    );

    vaylin.add_Message("Once, I had a family to anchor me. "
    "Now, their voices are but echoes, carried away by the same winds that scatter ash."
    );

    vaylin.add_Message("This pool reflects truth... but beware, "
    "for truth is as sharp as obsidian. Will you gaze upon its depths?"
    );

    vaylin.add_Message("Only those with the courage to face the darkness "
    "within themselves can alter the fate of this cursed realm."
    );

    vaylin.add_Message("Feed the balance, and perhaps the light may endure a while longer. "
    "Ignore it, and the end comes swifter than breath."
    );
        
    NPC kaedric("Kaedric, the Fallen Champion", "In the shattered remnants of "
    "The Infernal Forge, Kaedric slumps against\n"
    "a half-melted anvil. His once-pristine armor is scorched and broken,\n"
    "the crest of a forgotten kingdom barely visible on his chest plate.\n"
    "His face is scarred, and his weary eyes burn with embers of lost hope.\n"
    "A massive, chipped greatsword lies within arm's reach,\n"
    "untouched yet seemingly still waiting for battle."
    );

    kaedric.add_Message("I once carried the banner of a kingdom that "
    "stood proud against the tide of darkness. "
    "Now, that banner is ash, as is my resolve."
    );

    kaedric.add_Message("This forge was once the heart of creation, "
    "a place where weapons for heroes were born. "
    "Now... it only mocks my failure."
    );

    kaedric.add_Message("I've seen what lies beyond *The Abyssal Gate*. "
    "No sword nor shield can stop it. So tell me, why do you still fight?"
    );

    kaedric.add_Message("The world does not need a broken warrior. "
    "Yet here I remain, hoping against hope that someone else may succeed where I could not."
    );
    
    NPC sylfae("Sylfae, the Hollow Singer", "In the crumbled sanctuary "
    "of The Hollow Shrine, Sylfae drifts about\n"
    "as if weightless, her shimmering form flickering between corporeal and spectral.\n"
    "Her hauntingly melodic voice sings fragments of long-forgotten songs,\n"
    "which resonate eerily in the stone chamber.\n"
    "Her translucent eyes hold a sorrow that can never be mended."
    );

    sylfae.add_Message("Do you hear them? The songs of the lost, "
    "their voices woven into the cracks of this shrine..."
    );

    sylfae.add_Message("This altar was once a beacon of hope. "
    "Now, it crumbles beneath the weight of despair, "
    "much like the hearts of those who linger here."
    );

    sylfae.add_Message("I was bound to this place when the world began to fracture. "
    "I sing not for salvation, but to remind the stones that we once existed."
    );

    sylfae.add_Message("Perhaps you will succeed where so many have failed. "
    "Or perhaps, you will only join the choir of the forgotten."
    );
        
    NPC rask("Rask, the Wildwood Wanderer", "At the edge of The Whispering Cavern,\n"
    "a wiry man in patchy leather armor crouches near a firepit.\n"
    "Rask carries an assortment of tools and trinkets scavenged from the wilderness.\n"
    "His sharp, darting eyes suggest a life lived on edge,\n"
    "yet his sly grin hints at a streak of mischief."
    );

    rask.add_Message("Danger lurks in every shadow 'round here. "
    "But hey, one man's danger is another man's opportunity."
    );

    rask.add_Message("The faces in the cavern walls? Yeah, they whisper. "
    "Best advice? Don't listen too closely, or you might go mad like old Rask here."
    );

    rask.add_Message("I've wandered these lands all my life. "
    "Seen creatures that'll make your blood freeze. "
    "And trust me, it's the quiet ones you gotta watch."
    );

    rask.add_Message("You look like you've got guts. "
    "I mean. Keep 'em inside ya, though. That's my tip for surviving 'round here."
    );
    
    // add NPCs to locations
    woods->add_NPC(eryndor);
    pool->add_NPC(vaylin);
    infernal_forge->add_NPC(kaedric);
    shrine->add_NPC(sylfae);
    cavern->add_NPC(rask);

    // add items to locations
    obsidian_hall->add_Item(Item("Obsidian Emberfruit", 
    "A pitch-black fruit that burns faintly with an inner ember. "
    "Consuming it fills the air with the scent of ash and sweetness.", 150, 5));

    fallen_library->add_Item(Item("Ashen Page Loaf", 
    "A fragile loaf baked from powdered pages of enchanted, decayed tomes. "
    "It crumbles easily, yet radiates a faint magical glow.", 200, 4));

    pool->add_Item(Item("Glimmering Fungus", 
    "A bioluminescent mushroom that hums softly when touched. "
    "Its glowing spores grant a fleeting clarity to those who consume it.", 120, 2));

    gate->add_Item(Item("Voidberry Cluster", 
    "A cluster of deep purple berries that seem to absorb light, "
    "leaving a faint shadow where they rest.", 180, 3));

    shrine->add_Item(Item("Phantom Nectar",
    "A translucent, syrupy substance harvested from spectral blossoms "
    "found near broken altars. It tastes of forgotten dreams.", 250, 6));

    obsidian_hall->add_Item(Item("Blade of Shattered Light", 
    "A jagged sword forged from fractured obsidian, "
    "its edge glimmers faintly as though reflecting a forgotten light.", 0, 20.0));

    crystal_sanctum->add_Item(Item("Prismatic Shardstaff", 
    "A slender staff adorned with fragments of the sanctum's radiant crystals, "
    "its touch hums with boundless energy.", 0, 15.0));

    infernal_forge->add_Item(Item("Molten Gauntlets", 
    "A pair of gauntlets glowing with molten veins, "
    "crafted for wielding immense heat without harm. They pulse with fiery might.", 0, 10.0));

    fallen_library->add_Item(Item("Scroll of Ashbound Secrets", 
    "A delicate scroll inscribed with charred runes. "
    "Whispered chants from its text hold the power to ward off shadows.", 0, 3.0));

    shrine->add_Item(Item("Spectral Tear Amulet", 
    "An amulet formed from condensed ethereal energy. "
    "It glows faintly, resonating with the sorrowful songs of lost souls.", 0, 5.0));
    
    // add locations to the game
    locations.push_back(obsidian_hall);
    locations.push_back(crystal_sanctum);
    locations.push_back(fallen_library);
    locations.push_back(pool);
    locations.push_back(cavern);
    locations.push_back(infernal_forge);
    locations.push_back(shrine);
    locations.push_back(gate);
    locations.push_back(woods);

    // set up the story
    lore.push_back(R"(
    In ages long past, before the shadows stretched across the lands of Nytheris, 
    the world thrived in a delicate harmony forged by the elemental forces of light and darkness. 
    At the heart of this realm stood The Abyssal Gate, 
    a nexus where the energies of creation and destruction intertwined. 
    It was not a place of evil then, but a cosmic fulcrum, tended to by the Ancient Guardians, 
    primordial beings of immense power. These Guardians ensured that no force light 
    nor dark would overwhelm the other, for the balance was the lifeblood of the realm itself. 

    The balance endured for eons. The obsidian halls of the world hummed with the resonance of harmony. 
    The towering forests sang with life, their roots entwined with the crystalline sanctuaries of magic. 
    The forge of creation burned brightly, birthing artifacts of unimaginable power, 
    while libraries stood as repositories of eternal knowledge. Yet nothing lasts forever. 

    It began as a whisper, faint and insidious, rippling through the ether like a dark tide. 
    Unbeknownst to even the Guardians, the Gate was not a perfect instrument, it was a prison as well, 
    holding at bay an ancient, forgotten malevolence. This force, known only as The Shadow Within, 
    had been banished to the abyss during the worlds forging, 
    sealed away by the first Guardians in an act of ultimate sacrifice. 
    But over millennia, even the strongest seals can falter. The Gate began to crack. 

    The first sign of the worlds unraveling appeared in The Whispering Cavern, 
    where walls carved with grotesque faces began to murmur secrets not meant for mortal ears. 
    Travelers who ventured too close were driven mad by the haunting cacophony, 
    their screams joining the whispers in an unending symphony of despair. 

    Rask, the Wildwood Wanderer, was among the first to notice the shift, 
    his instincts honed by years of surviving in the wilds. 
    Yet even his sharp eyes could not foresee the depths of the coming calamity. 
    The corruption spread slowly at first, like ink spilled upon parchment. 
    From the Gate, tendrils of darkness began to seep into the realm, feeding on its essence. 
    The vibrant forests dimmed, their once-lush canopies withering into gnarled silhouettes. 
    The luminous crystals of The Crystal Sanctum, which once refracted the purest light, 
    fractured and turned to brittle shards, their hum of energy becoming an ominous drone. 

    The Guardians, sensing the disturbance, sought to mend the Gate. 
    They summoned the greatest heroes from across the land, among them Kaedric, 
    the Champion of the Forge, who carried a blade said to be unbreakable. 
    But as the Guardians drew close to the Gate, they found themselves deceived. 
    The Shadow Within, now partially free, wove its tendrils into their minds, 
    turning them against one another. The Guardians faltered, 
    and the balance they had upheld shattered. 

    Kaedric, once steadfast, witnessed the fall of the forge and the demise of his comrades, 
    leaving him a broken warrior. In the chaos, the Shadow Within spilled forth, 
    consuming all in its path. It fed upon the despair of the living, 
    twisting the minds of scholars, warriors, and kings alike. The great library, 
    a bastion of wisdom, crumbled under the weight of forgotten secrets. 
    Its enchanted texts were rendered to ash, their knowledge lost. 

    From the remnants emerged Vaylin, the Forsaken Seer, 
    her sight taken but her mind attuned to the whispers of the doomed realm. 
    The elves, guardians of the natural world, retreated into the woods, 
    their power waning as the corruption spread. Eryndor, the Enigmatic Sylvan, 
    took refuge in a hidden glade, using the last vestiges of his strength 
    to hold back the darkness. He knew the land needed a champion, 
    but his strength was fleeting, and his sustenance scarce. 

    Meanwhile, in the desolation of The Hollow Shrine, a haunting melody began to echo. 
    Sylfae, the Hollow Singer, bound to the crumbling altar, 
    sang songs of a time before the fall, her spectral voice a beacon for lost souls. 
    Her presence was both a comfort and a reminder of all that had been lost. 

    As the corruption spread, the Gate itself transformed into a swirling vortex of dark energy. 
    Its tendrils reached into the heavens, blotting out the sun and plunging 
    the realm into an eternal twilight. The air grew heavy with despair, 
    and even the bravest dared not approach its yawning maw. 

    The only hope left lay in the remnants of the past. The shattered artifacts of the forge, 
    the bioluminescent mushrooms of the pool, the spectral tears of the shrine, 
    these relics of a once-vibrant world held the power to push back the darkness, 
    but only if they were wielded by one who could restore the balance. 

    The Guardians had failed, the champions had fallen, and now the fate of 
    the world rested on the shoulders of those brave enough to rise amidst 
    the ashes of a dying realm. 

    Thus, the once-thriving land fell into ruin, 
    its people scattered, its forests darkened, and its heroes broken. 
    Yet in the shadows, a flicker of hope remained, a hope that the balance could be restored, 
    that the light might yet shine again, and that the whispers of the abyss might one day fall silent.
    )");

    lore.push_back(R"(
    As you place the final piece of sustenance into Eryndor's trembling hands, his glowing violet eyes flare with renewed vigor. 
    The elf, once frail and hunched, now rises to his full stature atop the moss-covered stone. 
    A surge of energy ripples through the glade, causing the bioluminescent fungi to blaze with light. 
    The forest seems to draw breath, its leaves quivering in anticipation. 
    Eryndor speaks, his voice a deep resonance that shakes the air itself. 

    "You have done what few dared to dream possible. 
    With this gift, I am no longer bound by the decay that seeped into my veins. 
    The corruption has spread far, but we may still turn back the tide. 
    Now, watch as the balance is restored!" 

    Eryndor raises his arms, and from his fingertips flows an ethereal, verdant light. 
    It snakes through the air, intertwining with the gnarled roots and branches of the dying woods. 
    The trees, once clawing at the sky in despair, begin to bloom with fresh life. 
    Flowers of impossible colors burst forth, and the sickly shadows retreat as the forest reclaims its essence. 
    A mighty roar echoes from the depths of the land, as if the earth itself is awakening. 

    But Eryndor is not done. His gaze turns northward, toward The Abyssal Gate, now a churning vortex of darkness and despair. 

    "The source of the corruption lies there," he declares, his voice resolute. 
    "No sword, no mortal hand may close that wound. But with the nourishment you have provided, I shall wield the light to seal it once more." 

    The forest parts before him as he strides forward, his robes billowing in the now-verdant breeze. 
    You follow closely, your heart pounding with both trepidation and hope. 
    The journey to the Gate is fraught with challenges; The faces in the Whispering Cavern howl in anger as Eryndor passes, 
    their sinister whispers momentarily amplified before his light silences them. 
    The Fallen Library groans under its ancient weight as the books seem to shiver, 
    their ashen pages turning back to life in his presence. 

    Finally, you reach The Abyssal Gate. It looms before you like a yawning wound, 
    its tendrils of darkness clawing at the heavens. 
    Eryndor steps forward and plunges his hands into the air, which ripples as if alive. 
    He chants in a language that no mortal can understand, his voice ringing with the harmony of the earth and the stars. 
    The Gate resists, its tendrils lashing out with ferocity, 
    but the light within Eryndor burns brighter with every passing moment. 
    It courses through him like a wildfire, illuminating the void and pushing back the encroaching darkness. 
    With a final, thunderous incantation, the Gate collapses in on itself, 
    its swirling vortex imploding into a single, radiant point of light that vanishes into the sky. 

    Silence falls over the land. The oppressive weight that hung over the world is lifted, 
    and for the first time in what feels like an eternity, 
    the sun breaks through the shrouded skies. A golden light spills across the realm, reviving the forests, 
    cleansing the halls of obsidian, and reigniting the forges of creation. 

    Eryndor turns to you, his form now faint and translucent, the toll of his sacrifice evident. 

    "The balance is restored," he whispers. 
    "But remember, it is fragile, as all things are. Guard it well, for the fate of this realm will always rest in the hands of those who walk its paths." 

    With those final words, he fades into the sunlight, leaving behind the glade now alive with vibrant energy. 
    The world is renewed, and though scars of the past remain, hope has taken root once more. 
    The lands of Nytheris are saved, thanks to your courage, persistence, and unwavering determination. 

    Congratulations! You have saved the realm, bringing light and life where there was once only shadow. 
    The stories of your deeds will echo through the ages, a testament to 
    the strength of even the smallest spark in the darkest of times.
    )");
}

// returns a random location from the locations list
Location* Game::random_location() {
    return locations[rand() % locations.size()];
}

// Game loop
void Game::play() {
    std::cout << "Welcome to my Zork based game! Enter '?' for commands.\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "\nThe Shattering of Balance: An Epic Origin Story\n";
    std::cout << lore[0];

    while (in_progress) {
        if (elf_calories_needed <= 0) {
            std::cout << lore[1];
            std::this_thread::sleep_for(std::chrono::minutes(4)); // if the user double clicks file, give them time to read ending
            break;                                                // before closing program
        }

        std::cout << "\nWhat is your command? ";
        std::string input;
        getline(std::cin, input);
        std::cout << "\n";
        
        // tokenize input
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        for (std::string s; iss >> s; )
            tokens.push_back(s);
        
        if (tokens.empty()) continue;
        
        std::string command = tokens[0];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        tokens.erase(tokens.begin());
        
        // checks if cmd exists, if exists invoke the member funct w/ funct ptrs
        if (cmds.find(command) != cmds.end()) {
            (this->*cmds[command])(tokens);
        } else {
            std::cout << "Invalid command.\n";
        }
    }
}

// command function implementations, remember objects have overloaded streams
// shows all cmds & current time
void Game::show_Help(std::vector<std::string>) {
    std::cout << "Available commands:\n";
    std::cout << "- ? (Show all commands)\n";
    std::cout << "- g (Show how to use all commands)\n";
    std::cout << "- q (Shows current objective)\n";
    std::cout << "- look (Reveal the details of your surroundings)\n";
    std::cout << "- go (Traverse to next location)\n";
    std::cout << "- meet (Return description of character)\n";
    std::cout << "- talk (Speak to a character)\n";
    std::cout << "- take (Pickup item)\n";
    std::cout << "- give (Drop item in current location)\n";
    std::cout << "- i (Show inventory)\n";
    std::cout << "- tp (Teleport to location)\n";
    std::cout << "- quit (Exit program)\n";
    
    std::time_t now = std::time(nullptr);
    std::cout << "\nCurrent time: " << std::put_time(std::localtime(&now), "%Y-%m-%d %I:%M:%S %p") << "\n";
}

// show how to use each cmd
void Game::guide(std::vector<std::string>) {
    std::cout << "Command Usage Guide:\n";
    std::cout << "- ? / help / info / cmds\n";
    std::cout << "- g / guide\n";
    std::cout << "- q / quest\n";
    std::cout << "- look\n";
    std::cout << "- go <direction>\n";
    std::cout << "- meet <NPC_Name>\n";
    std::cout << "- talk <NPC_Name>\n";
    std::cout << "- take <Item_Name>\n";
    std::cout << "- give <Item_Name>\n";
    std::cout << "- i / inventory\n";
    std::cout << "- tp / teleport <Location_Name>\n";
    std::cout << "- quit\n";
}

// shows the description of a npc
void Game::meet(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Missing name. Use 'meet <npc_name>'\n";
        return;
    }

    // combine tokens into a single NPC name
    std::string target_name = args[0];
    for (size_t i = 1; i < args.size(); ++i) {
        target_name += " " + args[i];
    }

    std::string tmp = target_name;

    std::transform(target_name.begin(), target_name.end(), target_name.begin(), ::tolower);

    const std::vector<NPC>& room_npcs = current_location->get_NPCs();

    // search for npc name in room_npcs
    std::vector<NPC>::const_iterator npc_it = std::find_if(room_npcs.begin(), room_npcs.end(), [target_name](const NPC& npc) {
        std::string npc_name = npc.get_Name();
        std::transform(npc_name.begin(), npc_name.end(), npc_name.begin(), ::tolower);
        return npc_name.find(target_name) != std::string::npos;
    });

    // if npc is found
    if (npc_it != room_npcs.end()) {
        std::cout << "You meet " << npc_it->get_Name() << ".\n";
        std::cout << "NPC description: " << npc_it->get_Desc() << "\n";
    } else {
        std::cout << "There is no one named " << tmp << " here.\n";
    }
}

// travel to another location
void Game::go(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Missing direction. Use 'go <direction>'\n";
        return;
    }

    if (args.size() > 1) {
        std::cout << "You can't go that way. Try a different direction.\n";
        return;
    }

    std::string target_direction = args[0];

    std::map<std::string, Location*> neighbors = current_location->get_Location();    // returns a map of directions for neighboring locations
    std::map<std::string, Location*>::iterator it = neighbors.find(target_direction); // returns the location of the direction specified

    // if location is found
    if (it != neighbors.end()) {
        current_location = (it->second); // set the current location to the new location
        current_location->set_Visited();
        std::cout << "You moved to: " << *current_location;
    } else {
        std::cout << "You can't go that way. Try a different direction.\n";
    }
}

// shows all items in inventory and total weight
void Game::show_items(std::vector<std::string>) {
    if (inventory.empty()) {
        std::cout << "You are not carrying any items.\n";
        return;
    }

    std::cout << "You are carrying the following items:\n";
    for (Item& item : inventory) {
        std::cout << "- " << item << "\n";
    }

    std::cout << "\nCurrent weight carried: " << current_weight << " lbs\n";
}

// picks up item from location
void Game::take(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Missing name. Use 'take <item>'\n";
        return;
    }

    // combine tokens into a single item name
    std::string target_item = args[0];
    for (size_t i = 1; i < args.size(); ++i) {
        target_item += " " + args[i];
    }

    std::string tmp = target_item; // this is to output what they typed if the item is not found

    std::transform(target_item.begin(), target_item.end(), target_item.begin(), ::tolower);

    std::vector<Item>& room_items = current_location->get_Items();

    // search for item name in room_items
    std::vector<Item>::const_iterator item_it = std::find_if(room_items.begin(), room_items.end(), [target_item](const Item& item) {
        std::string item_name;
        item_name = item.get_Name();
        std::transform(item_name.begin(), item_name.end(), item_name.begin(), ::tolower);
        return item_name.find(target_item) != std::string::npos;
    });

    // if item is found
    if (item_it != room_items.end()) {
        if (current_weight + item_it->get_Weight() > 20) {
            std::cout << "You cannot carry " << item_it->get_Name() 
                      << ". It would exceed your weight limit of 20 lbs.\n";
            return;
        }

        std::cout << "You picked up: " << item_it->get_Name() << "\n";

        inventory.push_back(*item_it);
        current_weight += item_it->get_Weight();
        room_items.erase(item_it);

    } else {
        std::cout << tmp << " not found in this location.\n";
    }
}

// drops an item in current location
void Game::give(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Missing name. Use 'give <item>'\n";
        return;
    }

    // combine tokens into a single item name
    std::string target_item = args[0];
    for (size_t i = 1; i < args.size(); ++i) {
        target_item += " " + args[i];
    }

    std::string tmp = target_item; // this is to output what they typed if the item is not found

    std::transform(target_item.begin(), target_item.end(), target_item.begin(), ::tolower);

    // search for item name in inventory
    std::vector<Item>::iterator item_it = std::find_if(inventory.begin(), inventory.end(), [&target_item](const Item& item) {
            std::string item_name = item.get_Name();
            std::transform(item_name.begin(), item_name.end(), item_name.begin(), ::tolower);
            return item_name.find(target_item) != std::string::npos;
        }
    );

    // if the item is found
    if (item_it != inventory.end()) { 
        if (current_location->get_Name() == "The Woods") {
            if (item_it->get_Calories() > 0) { // edible item

                // if erynador isnt on his last amount of calories, print message. If he is only remove calories (game ends w/lore)
                if (elf_calories_needed - item_it->get_Calories() >= 0) {
                    elf_calories_needed -= item_it->get_Calories();
                    std::cout << "You gave Eryndor: " << item_it->get_Name() << "\n";
                    std::cout << "The elf's required calories reduced by " 
                            << item_it->get_Calories() << ", " << elf_calories_needed << " left.\n";

                } else {
                    elf_calories_needed -= item_it->get_Calories();
                }

            } else { // non-edible item
                std::cout << "Eryndor glances at the unedible item with an unreadable expression,\n"
                "his glowing eyes narrowing slightly. Without a word, he raises a hand, and the air\n"
                "around you distorts. A surge of energy engulfs you, and the ground vanishes beneath\n"
                "your feet. When your vision clears, you find yourself in an entirely different location,\n"
                "disoriented and alone.\n";

                current_location = random_location();
                std::cout << "\nYou are magically transported to: " 
                          << current_location->get_Name() << "\n";
            }

        } else { 
            // If not in "the woods" simply drop item in current location
            current_location->add_Item(*item_it);
            std::cout << "You dropped: " << item_it->get_Name() << " in " 
                      << current_location->get_Name() << "\n";
        }

        current_weight -= item_it->get_Weight();
        inventory.erase(item_it);

    } else {
        std::cout << "You don't have an item matching \"" << tmp << "\"\n";
    }
}

// speaks to said NPC
void Game::talk(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Missing name. Use 'talk <npc_name>'\n";
        return;
    }

    // combine tokens into a single NPC name
    std::string target_name = args[0];
    for (size_t i = 1; i < args.size(); ++i) {
        target_name += " " + args[i];
    }

    std::string tmp = target_name; // this is to output what they typed if the item is not found

    std::transform(target_name.begin(), target_name.end(), target_name.begin(), ::tolower);

    std::vector<NPC>& room_npcs = current_location->get_NPCs();

    // search for npc name in room_npcs
    std::vector<NPC>::iterator npc_it = std::find_if(room_npcs.begin(), room_npcs.end(), [target_name](NPC& npc) {
        std::string npc_name = npc.get_Name();
        std::transform(npc_name.begin(), npc_name.end(), npc_name.begin(), ::tolower);
        return npc_name.find(target_name) != std::string::npos;
    });

    if (npc_it != room_npcs.end()) {
        std::cout << npc_it->get_Name() << " says: " << npc_it->get_Msg() << "\n";
    } else {
        std::cout << "There is no one named " << tmp << " here to talk to.\n";
    }
}

// examines the current environment
void Game::look(std::vector<std::string>) {
    std::cout << "Current Location: " << *current_location;
}

// shows current objective
void Game::quest(std::vector<std::string>) {
    std::cout << "Objective: Feed Eryndor enough calories to restore his strength\n";
}

// teleports player to location
void Game::teleport(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Missing name. Use 'tp <location_name>'\n";
        return;
    }

    // combine tokens into a single location name
    std::string target_location = args[0];
    for (size_t i = 1; i < args.size(); ++i) {
        target_location += " " + args[i];
    }

    std::string tmp = target_location; // this is to output what they typed if the item is not found

    std::transform(target_location.begin(), target_location.end(), target_location.begin(), ::tolower);

    // search for location name in room_npcs
    std::vector<Location*>::const_iterator location_it = std::find_if(locations.begin(), locations.end(), [target_location](Location* location) {
            std::string location_name = location->get_Name();
            std::transform(location_name.begin(), location_name.end(), location_name.begin(), ::tolower);
            return location_name == target_location;
        }
    );

    // If the location is found, teleport there
    if (location_it != locations.end()) {
        current_location = *location_it; 
        current_location->set_Visited();
        std::cout << "You have teleported to: " << *current_location; 
    } else {
        std::cout << "Location not found: " << tmp << "\n";
    }
}

// quits the game
void Game::quit(std::vector<std::string>) {
    std::cout << "Quitting game...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    in_progress = false;
}