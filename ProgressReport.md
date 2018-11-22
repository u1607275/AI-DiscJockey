#Artificial Intelligence Disc Jockey - Smart audio transitioning
##Matt Crewe U1607275
##University of Warwick, Department of Computer Science


Abstract
WRITE ABSTRACT LAST

Aim of the project. Description of the aim. How's its achieved. How far along the project I am
-----------

###Introduction and background

The goal of this project is have an audio player which blends multiple audio tracks together to give a smoother playback experience to the listener when changing between songs, automating the role of a DJ which you would find in a bar or night-club. Current examples of audio players such as Apple music*link to apple* and Spotify*link to spotify* try to achieve this state of automation using a technique known as cross-fade in which both tracks are played simultaneously while the volume of one track is lowered over time while the volume of the other is raised. These current examples use no analysis of the audio they’re playing in order to perform this operation and

Results can vary with some transitions being of very poor quality.

This can lead to some incoherent noise during song changes if any of the: key, tempo, or genre are mismatched.



		Almost all western music lies upon the chromatic scale, a scale which uses 12 notes all of the same distance from each other. It is however very rare for any one song to use every one of these notes; a select number of notes would be used to comprise each song. Each of these combinations of notes are assigned a new scale in which the song is said to be in with common scales being pentatonic or heptatonic.

		A few common properties that every song has are:

			Key, the scale of which the notes in a song use, along with a root note.  
			Tempo, measured in BPM. A measure of the speed that a song is played at.  
			Genre, the category of which the song falls into - often can be used to derive the types of instruments used in a piece of music but also the 'feel' of the song or 'vibe' that listener experiences when listening to the song.

		For 2 songs to sounds natural over top of each other they need to be played exactly the same tempo or for one BPM being an integer factor of the other. The key of both songs need to be same or share a majority of the same notes, 4 at an absolute minimum but preferably 5 or more. It may also be important for the genre of the songs to be similar so as to not conflict but as genre is not a quantifiable measure and this may be hard for the computer to automate, which is lucky as it is by far the least important factor (and possibly not at all necessary) in trying to smoothly blend tracks together. 




###System Requirements/Technology used

Not very powerful processor needed, I’m running a pentium II and works fine so far
Gstreamer multimedia pipeline with pluggins from the good library and bad library (But none from the ugly library)


###Objectives
A reminder of the objectives outlined to reach the ultimate goal of the project.
In the specification the order of the objectives indicated the order in which the would be completed but this is no longer the case. Objective 9 has been added which is to implement the audio transitions – this was always known to have been implemented but is now an explicit objective. The sub objectives under 
objective 9 are not exhaustive of all possible transitions, but instead the absolute minimum variety of transitions types.  
####Functional 
	1. Decode WAV files into signal that can be analysed (Done)
	2. Volume Normalisation (Not done)
	3. Song fade-in/out detection (Not done)
	4. Beat detection/Tempo analysis (Done)
	5. Key detection (Not done)
	6. Time stretching, pitch shifting - and changing over time (Done - not changing over time)
	7. Tempo and beat matching (Not done)
	8. Choose method of transitioning between audio sources using AI (Not done)
	9. Implement audio transitioning methods
		a. Cross-fade
		b. Loop and fade
		c. Instant switch

####Extensions
	1. Instrument/ layer separation (Not done)
	2. Other file type decoding (MP3, OGG, FLAC, ...) (Done)
	3. Take a library of songs and form a queue of music, not just 2 input files (Not done)
	4. Genre detection (Not done - unlikely I think)



###Project overview

Programmed in c. gcc used for compiling
git used for version control and GitHub used for repository store

gstreamer framework used for audio data file sourcing, decoding, manipulation, analysing and playback.




###Research

	Algorithms used for beat detection
	Algorithms used for key detection
	





Risk



###Project State

####Objectives Complete
Objective 1 and Extension objective 2 have been completed, the program can use any audio file format as a source and process into raw audio data for further analysis and modification. 
Objective 4 completed
Objective 6 completed although result given is not always accurate, results vary between different genres of music, and can be confused during periods of tempo changes or quieter parts of the songs where lower frequency notes are less frequent.

####Objectives behind schedule
Objectives 2 and 3 are set to be completed according to the timetable given in the original specification. This is due to the fact that the order of objectives that I’ve worked on has different from that originally given as I’ve decided that other qualities of the song are more important than the volume when it comes to progressing on the project. I’ve decided to work instead on tempo analysis and modification and pitch modification and to allow me to progress onto the AI part of the development sooner. Feel this is the harder part of the task




Testing



###Project Management




Legal, Ethical, and Professional issues??



Conclusion?


*Project specification goes here*



-----------------------------------
		#Artificial Intelligence Disc Jockey - Smart audio transitioning
		##Matt Crewe U1607275
		##University of Warwick, Department of Computer Science


		###Statement

		Spotify, Apple music and most other audio playback software have some form of cross-fade to make the change between song a bit smoother, and not a harsh single cut. All current examples of this use no intelligent method to make this transition and so many of these song changes can be very aurally offensive. The aim of this project is to use signal processing and artificial intelligence in order to either eliminate or significantly reduce the noticeable change between tracks so as to produce a better listening experience to the user.

		###Background

		Current examples of cross-fade use no intelligent algorithms, instead using a simple fixed duration fade-out on the first song overlaid by the second song with a fade-in of the same duration. This can lead to some incoherent noise during song changes if any of the: key, tempo, or genre are mismatched.

		Almost all western music lies upon the chromatic scale, a scale which uses 12 notes all of the same distance from each other. It is however very rare for any one song to use every one of these notes; a select number of notes would be used to comprise each song. Each of these combinations of notes are assigned a new scale in which the song is said to be in with common scales being pentatonic or heptatonic.

		A few common properties that every song has are:

			Key, the scale of which the notes in a song use, along with a root note.  
			Tempo, measured in BPM. A measure of the speed that a song is played at.  
			Genre, the category of which the song falls into - often can be used to derive the types of instruments used in a piece of music but also the 'feel' of the song or 'vibe' that listener experiences when listening to the song.

		For 2 songs to sounds natural over top of each other they need to be played exactly the same tempo or for one BPM being an integer factor of the other. The key of both songs need to be same or share a majority of the same notes, 4 at an absolute minimum but preferably 5 or more. It may also be important for the genre of the songs to be similar so as to not conflict but as genre is not a quantifiable measure and this may be hard for the computer to automate, which is lucky as it is by far the least important factor (and possibly not at all necessary) in trying to smoothly blend tracks together. 

		###Current Software

		Software for the purpose of mixing audio sources for smooth blending and transitioning has been in existence for great number of years. Numerous example of both paid and free open-source software performing these functions can be online. Mixxx~[7]~ is an example of an open-source piece of software designed for use by DJ's to replace the traditional vinyl disc DJ mixer decks. Serato DJ~[8]~ is another example of mixing software, this one being payroll software (where the user must pay a subscription each month to continue using the software). Both pieces of software and many other DJ mixing software enable high level control and manipulation of multiple audio signals. The problem with software of this nature is that it must be controlled manually for all audio control features other than the aforementioned cross-fade which uses no intelligence.  

		There are also many examples of audio analysis tools that will take a audio signal and return data relating to the source such as the tempo, pitch or time signature of beats. An example of a open-source software offering these features and more would be Aubio~[2]~. This however suffers the problem to the DJing software in which is use some intelligence to analyse the source but then does nothing with the data other than output it back to the user (print it to the command line). 

		I have found no examples of software that perform both audio analysis and manipulation based upon the data retrieved from the analysis.

		###Methodology
		I will be utilising an agile software development methodology throughout the development of this project, using a process similar to that of the scrum method. The scrum methodology is designed for small teams of developers; I as an individual developer will be utilising something similar as this will allow me to break the project down into sub-objectives, assigning a development period to each one that can be worked through sequentially. This allows for clear deadlines without removing flexibility from the project if any barriers are met or new features are desired.

		###Objectives

		####Functional 
			1. Decode WAV files into signal that can be analysed 
			2. Volume Normalisation
			3. Song fade-in/out detection
			4. Beat detection/Tempo analysis
			5. Key detection
			6. Time stretching, pitch shifting - and changing over time.
			7. Tempo and beat matching
			8. Choose method of transitioning between audio sources

		####Extensions
			1. Instrument/ layer separation
			2. Other file type decoding (MP3, OGG, FLAC, ...)
			3. Take a library of songs and form a queue of music, not just 2 input files
			4. Genre detection

		###Methods

		Audio files will be decoded using a library (possibly multiple to allow for multiple file types) but all other logic will be implemented by myself as it is important to understand how the data is being processed, so the necessary later modifications can be implemented with a lesser chance logical faults.

		Audio sources that have mismatched tempo or keys that don't work together must be modified in order to be overlaid. Fourier transforms can be used to gather empirical data about the audio signals which can be used to determine how the playback will need to be modified for smooth blending of multiple audio signals. Sources can be pitch shifted (a change in the pitch of each note to change the key the playback is in) or time stretched (a change in tempo of the audio without a change in pitch) in order to get the songs in a state where they can be blended together. Once the songs have been modified a method of transition
		A few methods for transitioning between songs:

			* hard jump cut at an appropriate place
			* beat and key match, cross-fade and then slowly change back to original BPM/pitch
			* Loop one track and start playing other over the top, bass and treble cut filters used to reduce noise so parts of both songs can be heard when 2 songs played simultaneously.

		####Function objectives
			1. WAV files (and possibly others file will types) will be decoded using a library.
			2. Volume normalisation will be performed using the RMS volume. Algorithm based on rules 
			3. Detected if the volume of the first or last parts of the audio file have a much smaller volume than a random sample of parts throughout the song. Algorithm based on rules with randomisation to find reference volumes
			4. Fourier transforms must sample at a frequency high enough to see peaks and troughs of beats. Volume should fluctuate at a rate of about 100Hz, peaks considered beats. Algorithm based on rules.
			5. Frequency of individual notes detected. If 440Hz assumed to be the note 'A' then scale can be found by viewing the ratio between notes. First note of song between 250hz and 500hz assumed to be root note. Key is a combination of these 2. Algorithm based on rules
			6. Raw data from audio source run through fixed rules algorithms to either time stretch, or pitch shift. Parameters used to determine the degree of stretch/shift and so can be slowly changed overtime.
			7. Use of system time to calculate when beat heads are going to occur. Second audio file playback started so that beat heads will align with one another. Fixed rules algorithm used.
			8. Machine learning or algorithm with rules used. 

		###Testing

		The code will be tested manually through out the whole development process. Initially will be tested as each sprint cycle is being worked on. The results will be determined if accurate by myself by a simple look at the output to see if response is appropriate or if any serious flaws in the system logic have occurred.

		At the end of each sprint cycle the objective will then be given a more thorough test against a library of audio files (some made specifically for test purposes), and songs that I have previously purchased, with known values for the result I'm looking for. The known values will be acquired through existing audio analysis tools, specifically Aubio~[2]~ (a command line program for Linux)

		Once the data returned from my software matches that from the existing software for every piece of test audio then the sprint cycle can be declared complete and progress on the next objective can begin.

		At the end of the project, the software will be testing using feedback from a set of human evaluators. Each evaluator will be given a variety of songs and audio clips where they can choose the order in which they are mixed so as not to give bias to songs that already transitioned well without the use of the AI DJ. Feedback will be given in the form of a questionnaire.

		###Timetable

		![Gantt Chart of predicted progress](ganttchart.png)
			
		###Risk assessment

		Support for the library used for audio decoding may be stopped during the development of my project. Other libraries performing the same functions could be found if this is the case or even the use of an older version of the library.

		A low risk could be that the algorithms implemented don't work as intended, however there are multiple audio source analysers that I've tested to work in the resources section which can be used as a reference for help should my own algorithms not work as intended



		###Legal, Social, and Ethical Considerations

		My project uses digital content (songs), a source with is protected by copyright laws. The sourcing of the media is entirely independent to this software and so no piracy concerns come from the possession, or execution of this software. No files will be output by this software, only the altering of playback so no infringement of copyright laws will take place. If this software is used to play music in a public venue a public performance royalty may need to be paid by the establishment, but is of no responsibility to the software or it's owner. 


		All libraries will be open-source and have licensing that allows for the free use of the software used. No library will be modified in the creation of my project.



		###Glossary

		Semi-tone - the distance between adjacent notes in the semi-chromatic scale  
		Heptatonic scale - A scale using 7 of the 12 chromatic notes  
		Pentatonic scale - A scale using 5 of the 12 chromatic notes
		Root note - A note which all the other notes in the song are said to relate to (typically the first note of the song).  
		BPM - Beats per minute  
		RMS - Root Mean Squared  
		Sprint cycle - A period of time assigned to the development of a single feature. Includes planning, implementation, and testing. Usually 1 - 4 weeks in length.  

		###Resources

			1. https://github.com/indrajithi/Audio-Visualizer
			2. https://aubio.org/
			3. https://gstreamer.freedesktop.org  
			5. https://www.lunaverus.com/cnn  
			6. https://github.com/ntrrgc/audio-heatmap
			7. https://github.com/mixxxdj/mixxx
			8. https://serato.com/dj/pro


