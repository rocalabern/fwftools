#' identifyHeader
identifyHeader <- function (text) {
  text <- gsub(" +","",text)
  text <- gsub("-+","-",text)
  return (text=="-")
}

#' getHeader
#' @export
getHeader <- function (file, maxlines=100) {
  textFile <- readLines (file, n=maxlines)

  found = FALSE
  i = 1
  while (i<length(textFile) && !found) {
    if (identifyHeader(textFile[i])) {
      found = TRUE
    } else {
      i <- i+1
    }
  }
  if (found) {
    searchResults = gregexpr(pattern ='-+',textFile[i])
    fieldPos = c(searchResults[[1]])
    widths = c(diff(fieldPos),nchar(textFile[i]) - sum(diff(fieldPos)))
    widths[1] = widths[1]-1
    widths[length(widths)] = widths[length(widths)]+1

    begin = fieldPos
    end = fieldPos+c(diff(fieldPos),1+nchar(textFile[i]) - sum(diff(fieldPos)))-2
  }

  o <- list()
  o[["found"]] = found
  if (found) {
    o[["skip"]] = i
    if (i>1) {
      o[["headers"]] = strsplit(gsub(" +"," ",textFile[i-1]),' ')[[1]]
    }
    o[["text"]] = textFile[i]
    o[["widths"]] = widths
    o[["begin"]] = begin
    o[["end"]] = end
  }
  return (o)
}