#include <gst/gst.h>
#include <math.h>

typedef struct pipelineData{
	GstElement *pipeline;
	GstElement *source, *sink, *decode, *convert, *timePitch;
}PipelineData;

//really horrible code that needs sorting out
static void pad_added_handler (GstElement *src, GstPad *new_pad, PipelineData *data) {
	GstPad *sink_pad = gst_element_get_static_pad (data->convert, "sink");
	GstPadLinkReturn ret;
	GstCaps *new_pad_caps = NULL;
	GstStructure *new_pad_struct = NULL;
	const gchar *new_pad_type = NULL;

	g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
	if (gst_pad_is_linked (sink_pad)) {
		g_print ("We are already linked. Ignoring.\n");
		goto exit;
	}

  /* Check the new pad's type */
	new_pad_caps = gst_pad_get_current_caps (new_pad);
	new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
	new_pad_type = gst_structure_get_name (new_pad_struct);
	if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
		g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
		goto exit;
	}

  /* Attempt the link */
	ret = gst_pad_link (new_pad, sink_pad);
	if (GST_PAD_LINK_FAILED (ret)) {
		g_print ("Type is '%s' but link failed.\n", new_pad_type);
	} else {
		g_print ("Link succeeded (type '%s').\n", new_pad_type);
	}

	exit:
  /* Unreference the new pad's caps, if we got them */
	if (new_pad_caps != NULL)
		gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
	gst_object_unref (sink_pad);
}

gboolean message_handler (GstBus * bus, GstMessage * message, gpointer data){
	if (message->type == GST_MESSAGE_ELEMENT) {
		const GstStructure *s = gst_message_get_structure (message);
		const gchar *name = gst_structure_get_name (s);
		GstClockTime endtime;

		g_print("Message");

	} else if (message->type == GST_MESSAGE_ERROR) {
		gchar  *debug;
		GError *error;

		gst_message_parse_error (message, &error, &debug);

		g_printerr ("Error: %s\n%s\n", error->message, debug);
		g_error_free (error);
		g_free (debug);

		//g_main_loop_quit (loop);
	}
	return TRUE;
}

int main(int argc, char *argv[]){

	double semitone = 2^(1/12);
	double tone = 2^(1/6);
	double tritone = 2^(1/2);

	double pitchShift = atof(argv[1]);
	float timeStretch = atof(argv[2]);

	g_print("%f",atof(argv[1])/12);

	PipelineData data;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	gst_init(&argc, &argv);

	/* Create the elements */
	data.source = gst_element_factory_make("filesrc", "source");
	data.decode = gst_element_factory_make("decodebin", "decode");
	data.convert = gst_element_factory_make("audioconvert", "convert");
	data.timePitch = gst_element_factory_make("pitch", "resample");
	data.sink = gst_element_factory_make("autoaudiosink", "sink");

	/* Create the empty pipeline */
	data.pipeline = gst_pipeline_new("pipeline");

	if(!data.pipeline || !data.sink || !data.source || !data.convert || !data.timePitch || !data.decode) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	//if(gst_uri_is_valid("home/matt/Music/River Purple/The River.wav")) g_print("not uri");

	g_object_set( G_OBJECT(data.source), "location", "/home/matt/Music/River.wav", NULL);
	//g_object_set( G_OBJECT(data.sink), "message-forward", 1, NULL);
	g_object_set( G_OBJECT(data.timePitch), "pitch", pitchShift, "tempo", timeStretch, NULL);

	/* Build the pipeline */
	gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.decode, data.convert, data.timePitch, data.sink, NULL);

	if(!gst_element_link(data.source, data.decode)) {
		g_printerr("Failed to link elements source to decoder\n");
		gst_object_unref(data.pipeline);
		return -1;
	}
	if(!gst_element_link_many(data.convert, data.timePitch, data.sink, NULL)) {
		g_printerr("Failed to link elements converter to sink\n");
		gst_object_unref(data.pipeline);
		return -1;
	}

	g_signal_connect(data.decode, "pad-added", G_CALLBACK (pad_added_handler), &data);

	bus = gst_element_get_bus(data.pipeline);
	gst_bus_add_watch(bus, message_handler, NULL);

	/* Start playing */
	ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
	if(ret == GST_STATE_CHANGE_FAILURE) {

		g_print("Failed to start up pipeline!\n");

		/* check if there is an error message with details on the bus */
		msg = gst_bus_poll(bus, GST_MESSAGE_ERROR, 0);
		if(msg) {
			GError *err = NULL;

			gst_message_parse_error(msg, &err, NULL);
			g_print("ERROR: %s\n", err->message);
			g_error_free(err);
			gst_message_unref(msg);
		}

		g_printerr("Unable to set the pipeline to the play state.\n");
		gst_element_set_state(data.pipeline, GST_STATE_NULL);
		gst_object_unref(data.pipeline);
		return -1;
	}

	/* Wait until error or EOS */
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* Parse message */
	if(msg != NULL) {
		GError *err;
		gchar *debug_info;

		switch(GST_MESSAGE_TYPE(msg)) {
			case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg, &err, &debug_info);
			g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
			g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
			g_clear_error(&err);
			g_free(debug_info);
			break;
			case GST_MESSAGE_EOS:
			g_print("End-Of-Stream reached.\n");
			break;
		}
		gst_message_unref(msg);
	}

	/* Free resources */
	gst_object_unref(bus);
	gst_element_set_state(data.pipeline, GST_STATE_NULL);
	gst_object_unref(data.pipeline);
	return 0;
}