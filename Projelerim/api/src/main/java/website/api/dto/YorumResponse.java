package website.api.dto;

import java.util.List;

import lombok.Data;

@Data
public class YorumResponse {
    private List<YorumDto> content;
    private int pageNumber;
    private int pageSize;
    private long totalElements;
    private int totalPages;
    private boolean last;
    
}
