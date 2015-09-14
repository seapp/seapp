//
// Generated file, do not edit! Created by nedtool 4.6 from applications/httptools/HttpMessages.msg.
//

#ifndef _HTTPMESSAGES_M_H_
#define _HTTPMESSAGES_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif



/**
 * Class generated from <tt>applications/httptools/HttpMessages.msg:93</tt> by nedtool.
 * <pre>
 * //
 * // Base class for HTTP messages
 * //
 * // NEW: The message definition has been migrated to OMNeT++ 4.0 and the latest INET version.
 * //
 * // @author Kristjan V. Jonsson
 * // @version 1.0
 * //
 * packet HttpBaseMessage
 * {
 *     @omitGetVerb(true);
 *     string targetUrl;               // The target URL - request set for browsers, echoed by servers.
 *     string originatorUrl = "";      // The originator URL. Only applicable for servers.
 *     int protocol = 11;              // 10 for http/1.0, 11 for http/1.1.
 *     bool keepAlive = true;          // The keep-alive header
 *     int serial = 0;                 // Convenience field which allows resource requests to be serially tagged for ease of analysis.
 *     string heading = "";                // The message heading - request string for requests, response for replies
 *     string payload = "";                // The payload field
 * }
 * </pre>
 */
class INET_API HttpBaseMessage : public ::cPacket
{
  protected:
    opp_string targetUrl_var;
    opp_string originatorUrl_var;
    int protocol_var;
    bool keepAlive_var;
    int serial_var;
    opp_string heading_var;
    opp_string payload_var;

  private:
    void copy(const HttpBaseMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const HttpBaseMessage&);

  public:
    HttpBaseMessage(const char *name=NULL, int kind=0);
    HttpBaseMessage(const HttpBaseMessage& other);
    virtual ~HttpBaseMessage();
    HttpBaseMessage& operator=(const HttpBaseMessage& other);
    virtual HttpBaseMessage *dup() const {return new HttpBaseMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * targetUrl() const;
    virtual void setTargetUrl(const char * targetUrl);
    virtual const char * originatorUrl() const;
    virtual void setOriginatorUrl(const char * originatorUrl);
    virtual int protocol() const;
    virtual void setProtocol(int protocol);
    virtual bool keepAlive() const;
    virtual void setKeepAlive(bool keepAlive);
    virtual int serial() const;
    virtual void setSerial(int serial);
    virtual const char * heading() const;
    virtual void setHeading(const char * heading);
    virtual const char * payload() const;
    virtual void setPayload(const char * payload);
};

inline void doPacking(cCommBuffer *b, HttpBaseMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, HttpBaseMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>applications/httptools/HttpMessages.msg:113</tt> by nedtool.
 * <pre>
 * //
 * // Message class for HTTP requests
 * //
 * // NEW: The message definition has been migrated to OMNeT++ 4.0 and the latest INET version.
 * //
 * // @author Kristjan V. Jonsson
 * // @version 1.0
 * //
 * packet HttpRequestMessage extends HttpBaseMessage
 * {
 *     @omitGetVerb(true);         // Dont append get to generated getter methods.
 *     bool badRequest = false;    // Set to true to simulate a bad request. Server answers w. 404.
 * }
 * </pre>
 */
class INET_API HttpRequestMessage : public ::HttpBaseMessage
{
  protected:
    bool badRequest_var;

  private:
    void copy(const HttpRequestMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const HttpRequestMessage&);

  public:
    HttpRequestMessage(const char *name=NULL, int kind=0);
    HttpRequestMessage(const HttpRequestMessage& other);
    virtual ~HttpRequestMessage();
    HttpRequestMessage& operator=(const HttpRequestMessage& other);
    virtual HttpRequestMessage *dup() const {return new HttpRequestMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool badRequest() const;
    virtual void setBadRequest(bool badRequest);
};

inline void doPacking(cCommBuffer *b, HttpRequestMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, HttpRequestMessage& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>applications/httptools/HttpMessages.msg:123</tt> by nedtool.
 * <pre>
 * //
 * // Content type of HTTP responses.
 * //
 * enum HttpContentType
 * {
 * 
 *     CT_UNKNOWN = 0;
 *     CT_HTML = 1;
 *     CT_IMAGE = 2;
 *     CT_TEXT = 3;
 * }
 * </pre>
 */
enum HttpContentType {
    CT_UNKNOWN = 0,
    CT_HTML = 1,
    CT_IMAGE = 2,
    CT_TEXT = 3
};

/**
 * Class generated from <tt>applications/httptools/HttpMessages.msg:140</tt> by nedtool.
 * <pre>
 * //
 * // Message class for HTTP replies
 * //
 * // NEW: The message definition has been migrated to OMNeT++ 4.0 and the latest INET version.
 * //
 * // @author Kristjan V. Jonsson
 * // @version 1.0
 * //
 * packet HttpReplyMessage extends HttpBaseMessage
 * {
 *     @omitGetVerb(true);
 *     int result = 0;      // e.g. 200 for OK, 404 for NOT FOUND.
 *     int contentType @enum(HttpContentType) = CT_UNKNOWN;
 * }
 * </pre>
 */
class INET_API HttpReplyMessage : public ::HttpBaseMessage
{
  protected:
    int result_var;
    int contentType_var;

  private:
    void copy(const HttpReplyMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const HttpReplyMessage&);

  public:
    HttpReplyMessage(const char *name=NULL, int kind=0);
    HttpReplyMessage(const HttpReplyMessage& other);
    virtual ~HttpReplyMessage();
    HttpReplyMessage& operator=(const HttpReplyMessage& other);
    virtual HttpReplyMessage *dup() const {return new HttpReplyMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int result() const;
    virtual void setResult(int result);
    virtual int contentType() const;
    virtual void setContentType(int contentType);
};

inline void doPacking(cCommBuffer *b, HttpReplyMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, HttpReplyMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef _HTTPMESSAGES_M_H_
