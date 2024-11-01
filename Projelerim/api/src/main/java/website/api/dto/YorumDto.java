/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package website.api.dto;

import lombok.Data;

@Data
public class YorumDto {
    private int id;
    private String username;
    private String nefretsebebi;
    private String startTime;
    private String yorum;
    private int like_count;
    private String photo_data_path;
}
