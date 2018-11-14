#include <gst/gst.h>

int main(int argc, char *argv[]){

	GstElement *pipeline, *source, *sink, *decode, *convert, *resample;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	gst_init (&argc, &argv);

	/* Create the elements */
	source = gst_element_factory_make ("filesrc", "source");
	decode = gst_element_factory_make("wavparse", "parse");
	sink = gst_element_factory_make ("autoaudiosink", "sink");

	/* Create the empty pipeline */
	pipeline = gst_pipeline_new ("pipeline");

	if (!pipeline || !sink || !source || !decode) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	//if(gst_uri_is_valid("home/matt/Music/River Purple/The River.wav")) g_print("not uri");

	g_object_set( G_OBJECT (source), "location", "/home/matt/Music/River.wav", NULL);


	/* Build the pipeline */
	gst_bin_add_many (GST_BIN (pipeline), source, decode, sink, NULL);

	if (!gst_element_link_many (source, decode, sink, NULL)) {
		g_printerr("Failed to link elements.\n");
		gst_object_unref (pipeline);
		return -1;
	}

	bus = gst_element_get_bus(pipeline);

	/* Start playing */
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {

		g_print ("Failed to start up pipeline!\n");

		/* check if there is an error message with details on the bus */
		msg = gst_bus_poll (bus, GST_MESSAGE_ERROR, 0);
		if (msg) {
			GError *err = NULL;

			gst_message_parse_error (msg, &err, NULL);
			g_print ("ERROR: %s\n", err->message);
			g_error_free (err);
			gst_message_unref (msg);
		}



		g_printerr ("Unable to set the pipeline to the play state.\n");
		gst_element_set_state (pipeline, GST_STATE_NULL);
		gst_object_unref (pipeline);
		return -1;
	}

	/* Wait until error or EOS */
	msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* Parse message */
	if (msg != NULL) {
		GError *err;
		gchar *debug_info;

		switch (GST_MESSAGE_TYPE (msg)) {
			case GST_MESSAGE_ERROR:
			gst_message_parse_error (msg, &err, &debug_info);
			g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
			g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
			g_clear_error (&err);
			g_free (debug_info);
			break;
			case GST_MESSAGE_EOS:
			g_print ("End-Of-Stream reached.\n");
			break;
			default:
        	/* We should not reach here because we only asked for ERRORs and EOS */
			g_printerr ("Unexpected message received.\n");
			break;
		}
		gst_message_unref (msg);
	}

	/* Free resources */
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	return 0;
}